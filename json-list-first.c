/*
 * Yonk JSON Node First Child Fetcher
 *
 * Copyright (c) 2018-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "json-int.h"

struct json *json_list_first (struct json *o)
{
	struct json_list *list = (void *) o;

	if (o->type == JSON_LIST || o->type == JSON_DICT)
		return list->head;

	return NULL;
}
