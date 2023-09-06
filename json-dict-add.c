/*
 * Yonk JSON Dictionary Node Adder
 *
 * Copyright (c) 2018-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <string.h>

#include "json-int.h"

bool json_dict_add (struct json *o, const char *key, struct json *c)
{
	struct json_dict *dict = (void *) o;

	if (o->type != JSON_DICT || c->next != NULL || c->key != NULL) {
		errno = EINVAL;
		return false;
	}

	if ((c->key = strdup (key)) == NULL)
		return false;

	*dict->end = c;
	dict->end = &c->next;
	return true;
}
