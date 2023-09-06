/*
 * Yonk JSON List Node Adder Generator
 *
 * Copyright (c) 2018-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef YONK_JSON_LIST_ADD_GEN
#define YONK_JSON_LIST_ADD_GEN  1

#include "json-int.h"

#define DEFINE_JSON_LIST_ADD_UNIT(name)					\
bool json_list_add_##name (struct json *o)				\
{									\
	struct json *child;						\
									\
	if ((child = json_alloc_##name ()) == NULL)			\
		return false;						\
									\
	if (json_list_add (o, child))					\
		return true;						\
									\
	json_put (child);						\
	return false;							\
}

#define DEFINE_JSON_LIST_ADD_VALUE(name, type)				\
bool json_list_add_##name (struct json *o, type value)			\
{									\
	struct json *child;						\
									\
	if ((child = json_alloc_##name (value)) == NULL)		\
		return false;						\
									\
	if (json_list_add (o, child))					\
		return true;						\
									\
	json_put (child);						\
	return false;							\
}

#define DEFINE_JSON_LIST_ADD_OBJECT(name)				\
struct json *json_list_add_##name (struct json *o)			\
{									\
	struct json *child;						\
									\
	if ((child = json_alloc_##name ()) == NULL)			\
		return child;						\
									\
	if (json_list_add (o, child))					\
		return child;						\
									\
	json_put (child);						\
	return NULL;							\
}

#endif  /* YONK_JSON_LIST_ADD_GEN */
