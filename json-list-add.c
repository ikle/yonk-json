/*
 * Yonk JSON List Node Adder
 *
 * Copyright (c) 2018-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>

#include "json-int.h"

bool json_list_add (struct json *o, struct json *c)
{
	struct json_list *list = (void *) o;

	if (o->type != JSON_LIST || c->next != NULL || c->key != NULL) {
		errno = EINVAL;
		return false;
	}

	*list->end = c;
	list->end = &c->next;
	return true;
}
