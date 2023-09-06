/*
 * Yonk JSON Node Next Sibling Fetcher
 *
 * Copyright (c) 2018-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "json-int.h"

struct json *json_list_next (struct json *o)
{
	return o->next;
}
