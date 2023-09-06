/*
 * Yonk JSON List Node Searcher
 *
 * Copyright (c) 2018-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "json-int.h"

struct json *json_list_lookup (struct json *o, size_t index)
{
	struct json_list *list = (void *) o;
	size_t i;

	if (o->type != JSON_LIST && o->type != JSON_DICT)
		return NULL;

	for (o = list->head, i = 0; o != NULL; o = o->next, ++i)
		if (i == index)
			return o;

	return NULL;
}
