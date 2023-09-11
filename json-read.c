/*
 * Yonk JSON Reader
 *
 * Copyright (c) 2018-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#include <yonk/json-io.h>

#ifdef DEBUG
#define json_debug(...)  fprintf (stderr, "D: " __VA_ARGS__)
#else
#define json_debug(...)
#endif

struct json_input {
	FILE *f;
	size_t i, avail;
	char line[256];
	char eol, point, type;
	struct json *node;
};

struct json_input *json_input_open (FILE *from)
{
	struct json_input *o;

	if ((o = malloc (sizeof (*o))) == NULL)
		return o;

	o->f     = from;
	o->i     = 0;
	o->avail = 0;
	o->point = localeconv()->decimal_point[0];
	return o;
}

void json_input_close (struct json_input *o)
{
	if (o != NULL)
		free (o);
}

static size_t in_pull (struct json_input *o)
{
	size_t avail = o->avail - o->i;

	memmove (o->line, o->line + o->i, avail);
	o->i = 0;
	o->avail = avail;

	o->avail += fread (o->line + avail, 1, sizeof (o->line) - avail, o->f);

	o->line[o->avail] = '\0';  /* can be eol */
	return o->avail;
}

static void in_skip_ws (struct json_input *o)
{
	for (; o->i < o->avail; ++o->i)
		switch (o->line[o->i]) {
		case '\t': case '\n': case '\r': case ' ':
			continue;
		default:
			return;
		}
}

static bool in_parse_number (struct json_input *o)
{
	size_t i;
	char *end;
	long l;
	double d;

	l = strtol (o->line + o->i, &end, 10);

	if ((i = end - o->line) >= o->avail) {
		in_pull (o);
		l = strtol (o->line + o->i, &end, 10);
	}

	if (*end != '.' && *end != 'e' && *end != 'E') {
		o->i = end - o->line;
		json_debug ("got int %ld\n", l);
		return (o->node = json_alloc_int (l)) != NULL;
	}

	if (*end == '.')
		*end = o->point;

	d = strtod (o->line + o->i, &end);

	if ((i = end - o->line) >= o->avail) {
		in_pull (o);
		d = strtod (o->line + o->i, &end);
	}

	o->i = end - o->line;
	json_debug ("got float %g\n", d);
	return (o->node = json_alloc_float (d)) != NULL;
}

/*
 * Note that we only support Basic Multilingual Plane of Unicode and do not
 * support control characters other than backspace, horizontal tab, newline,
 * form feed and carriage return.
 */
static bool in_parse_string (struct json_input *o)
{
	size_t i, s, d;

	in_pull (o);

	for (i = 1;; ++i)
		if (i >= o->avail)
			return false;
		else
		if (o->line[i] == '"')
			break;
		else
		if (o->line[i] == '\\')
			++i;

	o->i = i + 1;

	for (d = 0, s = 1; s < i; ++d, ++s)
		if (o->line[s] != '\\')
			o->line[d] = o->line[s];
		else
			switch (o->line[++s]) {
			case 'b':  o->line[d] = '\b'; break;
			case 't':  o->line[d] = '\t'; break;
			case 'n':  o->line[d] = '\n'; break;
			case 'f':  o->line[d] = '\f'; break;
			case 'r':  o->line[d] = '\r'; break;
			default:   o->line[d] = o->line[s]; break;
			}

	o->line[d] = '\0';
	json_debug ("got string '%s'\n", o->line);
	return (o->node = json_alloc_string (o->line)) != NULL;
}

static bool in_get_token (struct json_input *o);

static bool in_parse_list (struct json_input *o)
{
	struct json *list;

	++o->i;
	json_debug ("-> list\n");

	if ((list = json_alloc_list ()) == NULL)
		return false;

	while (in_get_token (o)) {
		if (o->type == ']') {
			o->node = list;
			json_debug ("<- list\n");
			return true;
		}

		if (o->type == ',' && !in_get_token (o))
			break;

		if (o->node == NULL || !json_list_add (list, o->node))
			break;
	}

	json_put (list);
	return false;
}

static bool in_parse_dict (struct json_input *o)
{
	struct json *dict, *k;
	const char *key;

	++o->i;
	json_debug ("-> dict\n");

	if ((dict = json_alloc_dict ()) == NULL)
		return false;

	for (;;) {
		if (!in_get_token (o))
			goto no_tok;

		if (o->type == '}') {
			o->node = dict;
			json_debug ("<- dict\n");
			return true;
		}

		if (o->type == ',' && !in_get_token (o))
			goto no_tok;

		if ((k = o->node) == NULL)
			goto no_tok;

		if ((key = json_get_string (k)) == NULL ||
		    !in_get_token (o))
			break;

		if (o->type == ':' && !in_get_token (o))
			break;

		if (o->node == NULL || !json_dict_add (dict, key, o->node))
			break;

		json_put (k);
	}

	json_put (k);
no_tok:
	json_put (dict);
	return false;
}

static bool in_get_token (struct json_input *o)
{
	o->node = NULL;

	if (o->avail == o->i && in_pull (o) == 0)
		return false;

	in_skip_ws (o);

	if (o->i == o->avail && in_pull (o) == 0)
		return false;

	o->type = o->line[o->i];

	switch (o->line[o->i]) {
	case 'n':
		if ((o->avail - o->i) < 4 && in_pull (o) < 4)
			return false;

		o->i += 4;
		json_debug ("got null\n");
		return (o->node = json_alloc_null ()) != NULL;
	case 'f':
		if ((o->avail - o->i) < 5 && in_pull (o) < 5)
			return false;

		o->i += 5;
		json_debug ("got false\n");
		return (o->node = json_alloc_bool (false)) != NULL;
	case 't':
		if ((o->avail - o->i) < 4 && in_pull (o) < 4)
			return false;

		o->i += 4;
		json_debug ("got true\n");
		return (o->node = json_alloc_bool (true)) != NULL;
	case '-':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		return in_parse_number (o);
	case '"':
		return in_parse_string (o);
	case '[':
		return in_parse_list (o);
	case '{':
		return in_parse_dict (o);
	case ',': case ':': case ']': case '}':
		++o->i;
		return true;
	}

	return false;
}

/*
 * Note that if you are looking for a way to validate JSON, then this
 * function is definitely not what you need.
 *
 * The parser should correctly parse a valid input, but its behavior is
 * undefined for an invalid input (UB). The only limitation for invalid
 * input is non-destructive behavior (for security reasons).
 */
struct json *json_read (struct json_input *o)
{
	errno = 0;
	in_get_token (o);

	if (o->node != NULL)
		return o->node;

	if (errno == 0)
		errno = EINVAL;

	return NULL;
}
