/*
 * Yonk JSON Core Test
 *
 * Copyright (c) 2018-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <yonk/json-io.h>

static bool test_dict (struct json *root)
{
	struct json *list;

	return	json_dict_add_null   (root, "null")			&&
		json_dict_add_bool   (root, "bool",   false)		&&
		json_dict_add_int    (root, "int",    100)		&&
		json_dict_add_float  (root, "float",  4.0)		&&
		json_dict_add_string (root, "string", "test\bt")	&&
		(list = json_dict_add_list (root, "list")) != NULL	&&
		json_list_add_null   (list)				&&
		json_list_add_bool   (list, false)			&&
		json_list_add_int    (list, 12)				&&
		json_list_add_float  (list, 3.14)			&&
		json_list_add_string (list, "okay")			&&
		json_list_add_list   (list) != NULL			&&
		json_list_add_dict   (list) != NULL			&&
		json_dict_add_dict   (root, "dict") != NULL		&&
		json_write (stdout, root)				&&
		fputc ('\n', stdout) != EOF;
}

static bool test_dict_lookup (struct json *root)
{
	const struct json *o = json_dict_lookup (root, "float");

	return	o != NULL &&
		json_write (stdout, o) && fputc ('\n', stdout) != EOF;
}

static bool test_get_put (struct json *root)
{
	struct json *list = json_dict_lookup (root, "list");
	bool ok;

	if (list != NULL)
		json_get (list);

	json_put (root);

	ok =	list != NULL &&
		json_write (stdout, list) && fputc ('\n', stdout) != EOF;

	if (list != NULL)
		json_put (list);

	return ok;
}

int main (int argc, char *argv[])
{
	struct json *root;

	if ((root = json_alloc_dict ()) == NULL) {
		perror ("E: root dict alloc");
		return 1;
	}

	if (!test_dict (root)) {
		json_put (root);
		perror ("E: build and show test dict");
		return 1;
	}

	if (!test_dict_lookup (root)) {
		json_put (root);
		perror ("E: lookup dict and show result");
		return 1;
	}

	if (!test_get_put (root)) {
		perror ("E: get and show list");
		return 1;
	}

	return 0;
}
