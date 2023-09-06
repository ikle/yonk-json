/*
 * Yonk JSON Node Holder
 *
 * Copyright (c) 2018-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "json-int.h"

struct json *json_get (struct json *o)
{
	++o->refs;

	return o;
}
