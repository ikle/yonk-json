/*
 * Yonk JSON Writer
 *
 * Copyright (c) 2018-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <yonk/json-io.h>

#include "json-int.h"

/*
 * Note that we only support Basic Multilingual Plane of Unicode and do not
 * support control characters other than backspace, horizontal tab, newline,
 * form feed and carriage return.
 */
static bool json_put_char (FILE *to, char c)
{
	switch (c) {
	case '\b':	return fputs ("\\b",  to) != EOF;
	case '\t':	return fputs ("\\t",  to) != EOF;
	case '\n':	return fputs ("\\n",  to) != EOF;
	case '\f':	return fputs ("\\f",  to) != EOF;
	case '\r':	return fputs ("\\r",  to) != EOF;
	case '"':	return fputs ("\\\"", to) != EOF;
	case '\\':	return fputs ("\\\\", to) != EOF;
	default:	return fputc (c,      to) != EOF;
	}
}

static bool json_put_string (FILE *to, const char *s)
{
	const char *p;

	if (fputc ('"', to) == EOF)
		return false;

	for (p = s; *p != '\0'; ++p)
		if (!json_put_char (to, *p))
			return false;

	return fputc ('"', to) != EOF;
}

bool json_write_node (FILE *to, const struct json *o, bool dict)
{
	const struct json_list *list = (void *) o;
	const struct json *c;

	if (dict && (!json_put_string (to, o->key) || fputc (':', to) == EOF))
		return false;

	switch (o->type) {
	case JSON_NULL:
		return fprintf (to, "null") > 0;
	case JSON_BOOL:
		return fprintf (to, "%s", ((struct json_bool *) o)->value ?
					  "true" : "false") > 0;
	case JSON_INT:
		return fprintf (to, "%ld", ((struct json_int *) o)->value) > 0;
	case JSON_FLOAT:
		return fprintf (to, "%g", ((struct json_float *) o)->value) > 0;
	case JSON_STRING:
		return json_put_string (to, ((struct json_string *) o)->value);
	case JSON_LIST:
	case JSON_DICT:
		break;
	default:
		return false;
	}

	if (fputc (o->type == JSON_DICT ? '{': '[', to) == EOF)
		return false;

	if ((c = list->head) != NULL) {
		if (!json_write_node (to, c, o->type == JSON_DICT))
			return false;

		for (c = c->next; c != NULL; c = c->next)
			if (fprintf (to, ",") < 0 ||
			    !json_write_node (to, c, o->type == JSON_DICT))
				return false;
	}

	return fputc (o->type == JSON_DICT ? '}': ']', to) != EOF;
}

bool json_write (FILE *to, const struct json *o)
{
	return json_write_node (to, o, false);
}
