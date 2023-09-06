/*
 * Yonk JSON String Node Allocator
 *
 * Copyright (c) 2018-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>
#include <string.h>

#include "json-int.h"

struct json *json_alloc_string (const char *value)
{
	struct json_string *o;

	if ((o = malloc (sizeof (*o) + strlen (value))) != NULL) {
		o->next = NULL;
		o->refs = 1;
		o->key  = NULL;
		o->type = JSON_STRING;

		strcpy (o->value, value);
	}

	return (void *) o;
}
