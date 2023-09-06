/*
 * Yonk JSON Boolean Node Allocator
 *
 * Copyright (c) 2018-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>

#include "json-int.h"

struct json *json_alloc_bool (bool value)
{
	struct json_bool *o;

	if ((o = malloc (sizeof (*o))) != NULL) {
		o->next  = NULL;
		o->refs  = 1;
		o->key   = NULL;
		o->type  = JSON_BOOL;
		o->value = value;
	}

	return (void *) o;
}
