/*
 * Yonk JSON List Node Null Adder
 *
 * Copyright (c) 2018-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "json-int.h"

bool json_list_add_null (struct json *o)
{
	struct json *child;

	if ((child = json_alloc_null ()) == NULL)
		return false;

	if (json_list_add (o, child))
		return true;

	json_put (child);
	return false;
}
