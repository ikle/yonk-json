/*
 * Yonk JSON Dictionary Node Adder Generator
 *
 * Copyright (c) 2018-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef YONK_JSON_DICT_ADD_GEN
#define YONK_JSON_DICT_ADD_GEN  1

#include "json-int.h"

#define DEFINE_JSON_DICT_ADD_UNIT(name)					\
bool json_dict_add_##name (struct json *o, const char *key)		\
{									\
	struct json *child;						\
									\
	if ((child = json_alloc_##name ()) == NULL)			\
		return false;						\
									\
	if (json_dict_add (o, key, child))				\
		return true;						\
									\
	json_put (child);						\
	return false;							\
}

#define DEFINE_JSON_DICT_ADD_VALUE(name, type)				\
bool json_dict_add_##name (struct json *o, const char *key, type value)	\
{									\
	struct json *child;						\
									\
	if ((child = json_alloc_##name (value)) == NULL)		\
		return false;						\
									\
	if (json_dict_add (o, key, child))				\
		return true;						\
									\
	json_put (child);						\
	return false;							\
}

#define DEFINE_JSON_DICT_ADD_OBJECT(name)				\
struct json *json_dict_add_##name (struct json *o, const char *key)	\
{									\
	struct json *child;						\
									\
	if ((child = json_alloc_##name ()) == NULL)			\
		return child;						\
									\
	if (json_dict_add (o, key, child))				\
		return child;						\
									\
	json_put (child);						\
	return NULL;							\
}

#endif  /* YONK_JSON_DICT_ADD_GEN */
