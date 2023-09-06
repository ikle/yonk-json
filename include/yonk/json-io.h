/*
 * Yonk JSON I/O API
 *
 * Copyright (c) 2018-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef YONK_JSON_IO_H
#define YONK_JSON_IO_H  1

#include <stdio.h>
#include <yonk/json.h>

bool json_write (FILE *to, const struct json *o);

#endif  /* YONK_JSON_IO_H */
