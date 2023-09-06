/*
 * Yonk JSON Node String Fetcher
 *
 * Copyright (c) 2018-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "json-int.h"

const char *json_get_string (struct json *o)
{
	if (o->type == JSON_STRING)
		return ((struct json_string *) o)->value;

	return NULL;
}
