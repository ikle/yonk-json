/*
 * Yonk JSON Node Boolean Fetcher
 *
 * Copyright (c) 2018-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "json-int.h"

bool json_get_bool (struct json *o)
{
	if (o->type == JSON_BOOL)
		return ((struct json_bool *) o)->value;

	return false;
}
