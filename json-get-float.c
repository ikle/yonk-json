/*
 * Yonk JSON Node Floating Number Fetcher
 *
 * Copyright (c) 2018-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "json-int.h"

double json_get_float (struct json *o)
{
	switch (o->type) {
	case JSON_INT:
		return ((struct json_int *) o)->value;

	case JSON_FLOAT:
		return ((struct json_float *) o)->value;
	}

	return 0.0;
}
