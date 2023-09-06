/*
 * Yonk JSON Floating Number Node Allocator
 *
 * Copyright (c) 2018-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>

#include "json-int.h"

struct json *json_alloc_float (double value)
{
	struct json_float *o;

	if ((o = malloc (sizeof (*o))) != NULL) {
		o->next  = NULL;
		o->refs  = 1;
		o->key   = NULL;
		o->type  = JSON_FLOAT;
		o->value = value;
	}

	return (void *) o;
}
