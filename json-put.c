/*
 * Yonk JSON Node Releaser
 *
 * Copyright (c) 2018-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>

#include "json-int.h"

void json_put (struct json *o)
{
	struct json_list *list = (void *) o;
	struct json *c, *next;

	if (--o->refs != 0)
		return;

	if (o->type == JSON_LIST || o->type == JSON_DICT)
		for (c = list->head; c != NULL; c = next) {
			next = c->next;
			json_put (c);
		}

	free (o->key);
	free (o);
}
