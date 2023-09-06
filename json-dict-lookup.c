/*
 * Yonk JSON Dictionary Node Searcher
 *
 * Copyright (c) 2018-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <string.h>

#include "json-int.h"

struct json *json_dict_lookup (struct json *o, const char *key)
{
	struct json_list *list = (void *) o;

	if (o->type != JSON_DICT)
		return NULL;

	for (o = list->head; o != NULL; o = o->next)
		if (strcmp (o->key, key) == 0)
			return o;

	return NULL;
}
