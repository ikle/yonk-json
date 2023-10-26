/*
 * Yonk JSON Library
 *
 * Copyright (c) 2018-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef YONK_JSON_H
#define YONK_JSON_H  1

#include <stdbool.h>
#include <stddef.h>

struct json *json_alloc_null   (void);
struct json *json_alloc_bool   (bool value);
struct json *json_alloc_int    (long value);
struct json *json_alloc_float  (double value);
struct json *json_alloc_string (const char *value);
struct json *json_alloc_list   (void);
struct json *json_alloc_dict   (void);

struct json *json_get (struct json *o);
void json_put (struct json *o);

bool        json_get_bool   (struct json *o);
long        json_get_int    (struct json *o);
double      json_get_float  (struct json *o);
const char *json_get_string (struct json *o);

struct json *json_list_first  (struct json *o);
struct json *json_list_next   (struct json *o);
struct json *json_list_lookup (struct json *o, size_t index);
struct json *json_dict_lookup (struct json *o, const char *key);

bool json_list_add (struct json *o, struct json *child);
bool json_dict_add (struct json *o, const char *key, struct json *value);

bool json_list_add_null   (struct json *o);
bool json_list_add_bool   (struct json *o, bool value);
bool json_list_add_int    (struct json *o, long value);
bool json_list_add_float  (struct json *o, double value);
bool json_list_add_string (struct json *o, const char *value);

struct json *json_list_add_list (struct json *o);
struct json *json_list_add_dict (struct json *o);

bool json_dict_add_null   (struct json *o, const char *key);
bool json_dict_add_bool   (struct json *o, const char *key, bool value);
bool json_dict_add_int    (struct json *o, const char *key, long value);
bool json_dict_add_float  (struct json *o, const char *key, double value);
bool json_dict_add_string (struct json *o, const char *key, const char *value);

struct json *json_dict_add_list (struct json *o, const char *key);
struct json *json_dict_add_dict (struct json *o, const char *key);

struct json *json_read_blob (const char *data, size_t len);

#endif  /* YONK_JSON_H */
