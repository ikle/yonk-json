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

struct json_input *json_input_open_file (FILE *from);
void json_input_close (struct json_input *o);

/*
 * Note that if you are looking for a way to validate JSON, then this
 * function is definitely not what you need.
 *
 * The parser should correctly parse a valid input, but its behavior is
 * undefined for an invalid input (UB). The only limitation for invalid
 * input is non-destructive behavior (for security reasons).
 */
struct json *json_read (struct json_input *o);

bool json_write (FILE *to, const struct json *o);

#endif  /* YONK_JSON_IO_H */
