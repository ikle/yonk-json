/*
 * Yonk JSON Library Internals
 *
 * Copyright (c) 2018-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef YONK_JSON_INT_H
#define YONK_JSON_INT_H  1

#include <yonk/json.h>

enum json_type {
	JSON_NULL	= 0,
	JSON_BOOL	= 1,
	JSON_INT	= 2,
	JSON_FLOAT	= 3,
	JSON_STRING	= 4,
	JSON_LIST	= 5,
	JSON_DICT	= 6,
};

#define YONK_JSON_COMMON	\
	struct json *next;	\
	size_t refs;		\
	char  *key;		\
	int    type;

struct json {
	YONK_JSON_COMMON
};

struct json_bool {
	YONK_JSON_COMMON
	bool   value;
};

struct json_int {
	YONK_JSON_COMMON
	long   value;
};

struct json_float {
	YONK_JSON_COMMON
	double value;
};

struct json_string {
	YONK_JSON_COMMON
	char   value[1];	/* at least '\0' exists */
};

struct json_list {
	YONK_JSON_COMMON
	struct json *head, **end;
};

struct json_dict {
	YONK_JSON_COMMON
	struct json *head, **end;
};

#endif  /* YONK_JSON_INT_H */
