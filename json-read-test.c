/*
 * Yonk JSON Reader Test
 *
 * Copyright (c) 2018-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <yonk/json-io.h>

int main (int argc, char *argv[])
{
	struct json_input *in;
	struct json *o;

	if ((in = json_input_open_file (stdin)) == NULL) {
		perror ("E: json_input_alloc");
		return 1;
	}

	while ((o = json_read (in)) != NULL) {
		if (!json_write (stdout, o))
			goto no_write;

		fputc ('\n', stdout);
		json_put (o);
	}

	json_input_close (in);
	return 0;
no_write:
	perror ("E: json_write");
	json_put (o);
	json_input_close (in);
	return 1;
}
