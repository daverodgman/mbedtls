/**
 *  Constant-time functions
 */
/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 *
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if
 * not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#ifndef MBEDTLS_CONSTANT_TIME_H
#define MBEDTLS_CONSTANT_TIME_H

#include <stddef.h>

/** Constant-time buffer comparison without branches.
 *
 * This is equivalent to the standard memcmp function, but is likely to be
 * compiled to code using bitwise operations rather than a branch, such that
 * the time taken is constant w.r.t. the data pointed to by \p a and \p b,
 * and w.r.t. whether \p a and \p b are equal or not. It is not constant-time
 * w.r.t. \p n .
 *
 * This function can be used to write constant-time code by replacing branches
 * with bit operations using masks.
 *
 * \param a     Pointer to the first buffer, containing at least \p n bytes. May not be NULL.
 * \param b     Pointer to the second buffer, containing at least \p n bytes. May not be NULL.
 * \param n     The number of bytes to compare.
 *
 * \return      Zero if the contents of the two buffers are the same,
 *              otherwise non-zero.
 */
int mbedtls_ct_memcmp(const void *a,
                      const void *b,
                      size_t n);

#endif /* MBEDTLS_CONSTANT_TIME_H */
