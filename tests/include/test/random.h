/**
 * \file random.h
 *
 * \brief   This file contains the prototypes of helper functions to generate
 *          random numbers for the purpose of testing.
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

#ifndef TEST_RANDOM_H
#define TEST_RANDOM_H

#include "mbedtls/build_info.h"

#include <stddef.h>
#include <stdint.h>

typedef struct {
    unsigned char *buf; /* Pointer to a buffer of length bytes. */
    size_t length;
    /* If fallback_f_rng is NULL, fail after delivering length bytes. */
    int (*fallback_f_rng)(void *, unsigned char *, size_t);
    void *fallback_p_rng;
} mbedtls_test_rnd_buf_info;

/**
 * Info structure for the pseudo random function
 *
 * Key should be set at the start to a test-unique value.
 * Do not forget endianness!
 * State( v0, v1 ) should be set to zero.
 */
typedef struct {
    uint32_t key[16];
    uint32_t v0, v1;
} mbedtls_test_rnd_pseudo_info;

/**
 * This function just returns data from rand().
 * Although predictable and often similar on multiple
 * runs, this does not result in identical random on
 * each run. So do not use this if the results of a
 * test depend on the random data that is generated.
 *
 * rng_state shall be NULL.
 */
int mbedtls_test_rnd_std_rand(void *rng_state,
                              unsigned char *output,
                              size_t len);

/**
 * This function only returns zeros.
 *
 * \p rng_state shall be \c NULL.
 */
int mbedtls_test_rnd_zero_rand(void *rng_state,
                               unsigned char *output,
                               size_t len);

/**
 * This function returns random data based on a buffer it receives.
 *
 * \p rng_state shall be a pointer to a #mbedtls_test_rnd_buf_info structure.
 *
 * The number of bytes released from the buffer on each call to
 * the random function is specified by \p len.
 *
 * After the buffer is empty, this function will call the fallback RNG in the
 * #mbedtls_test_rnd_buf_info structure if there is one, and
 * will return #MBEDTLS_ERR_ENTROPY_SOURCE_FAILED otherwise.
 */
int mbedtls_test_rnd_buffer_rand(void *rng_state,
                                 unsigned char *output,
                                 size_t len);

/**
 * This function returns random based on a pseudo random function.
 * This means the results should be identical on all systems.
 * Pseudo random is based on the XTEA encryption algorithm to
 * generate pseudorandom.
 *
 * \p rng_state shall be a pointer to a #mbedtls_test_rnd_pseudo_info structure.
 */
int mbedtls_test_rnd_pseudo_rand(void *rng_state,
                                 unsigned char *output,
                                 size_t len);

#endif /* TEST_RANDOM_H */
