/*
 * Yonk JSON Blob Reader
 *
 * Copyright (c) 2018-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <string.h>

#include <yonk/json-io.h>

struct blob {
	const char *data;
	size_t len;
};

static size_t blob_read (void *buf, size_t len, void *cookie)
{
	struct blob *o = cookie;

	if (len > o->len)
		len = o->len;

	memcpy (buf, o->data, len);

	o->len  -= len;
	o->data += len;
	return len;
}

struct json *json_read_blob (const char *data, size_t len)
{
	struct blob c = { data, len };
	struct json_input *in;
	struct json *o;

	if ((in = json_input_open (blob_read, &c)) == NULL)
		return NULL;

	o = json_read (in);
	json_input_close (in);
	return o;
}
