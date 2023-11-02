/*
 * Test driver for cipher functions
 */
/*  Copyright The Mbed TLS Contributors
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

#ifndef PSA_CRYPTO_TEST_DRIVERS_CIPHER_H
#define PSA_CRYPTO_TEST_DRIVERS_CIPHER_H

#include "mbedtls/build_info.h"

#if defined(PSA_CRYPTO_DRIVER_TEST)
#include <psa/crypto_driver_common.h>
#include <psa/crypto.h>

#include "mbedtls/cipher.h"

typedef struct {
    /* If non-null, on success, copy this to the output. */
    void *forced_output;
    size_t forced_output_length;
    /* If not PSA_SUCCESS, return this error code instead of processing the
     * function call. */
    psa_status_t forced_status;
    /* Count the amount of times one of the cipher driver functions is called. */
    unsigned long hits;
} mbedtls_test_driver_cipher_hooks_t;

#define MBEDTLS_TEST_DRIVER_CIPHER_INIT { NULL, 0, PSA_SUCCESS, 0 }
static inline mbedtls_test_driver_cipher_hooks_t
mbedtls_test_driver_cipher_hooks_init(void)
{
    const mbedtls_test_driver_cipher_hooks_t v = MBEDTLS_TEST_DRIVER_CIPHER_INIT;
    return v;
}

extern mbedtls_test_driver_cipher_hooks_t mbedtls_test_driver_cipher_hooks;

psa_status_t mbedtls_test_transparent_cipher_encrypt(
    const psa_key_attributes_t *attributes,
    const uint8_t *key, size_t key_length,
    psa_algorithm_t alg,
    const uint8_t *iv, size_t iv_length,
    const uint8_t *input, size_t input_length,
    uint8_t *output, size_t output_size, size_t *output_length);

psa_status_t mbedtls_test_transparent_cipher_decrypt(
    const psa_key_attributes_t *attributes,
    const uint8_t *key, size_t key_length,
    psa_algorithm_t alg,
    const uint8_t *input, size_t input_length,
    uint8_t *output, size_t output_size, size_t *output_length);

psa_status_t mbedtls_test_transparent_cipher_encrypt_setup(
    mbedtls_transparent_test_driver_cipher_operation_t *operation,
    const psa_key_attributes_t *attributes,
    const uint8_t *key, size_t key_length,
    psa_algorithm_t alg);

psa_status_t mbedtls_test_transparent_cipher_decrypt_setup(
    mbedtls_transparent_test_driver_cipher_operation_t *operation,
    const psa_key_attributes_t *attributes,
    const uint8_t *key, size_t key_length,
    psa_algorithm_t alg);

psa_status_t mbedtls_test_transparent_cipher_abort(
    mbedtls_transparent_test_driver_cipher_operation_t *operation);

psa_status_t mbedtls_test_transparent_cipher_set_iv(
    mbedtls_transparent_test_driver_cipher_operation_t *operation,
    const uint8_t *iv, size_t iv_length);

psa_status_t mbedtls_test_transparent_cipher_update(
    mbedtls_transparent_test_driver_cipher_operation_t *operation,
    const uint8_t *input, size_t input_length,
    uint8_t *output, size_t output_size, size_t *output_length);

psa_status_t mbedtls_test_transparent_cipher_finish(
    mbedtls_transparent_test_driver_cipher_operation_t *operation,
    uint8_t *output, size_t output_size, size_t *output_length);

/*
 * opaque versions
 */
psa_status_t mbedtls_test_opaque_cipher_encrypt(
    const psa_key_attributes_t *attributes,
    const uint8_t *key, size_t key_length,
    psa_algorithm_t alg,
    const uint8_t *iv, size_t iv_length,
    const uint8_t *input, size_t input_length,
    uint8_t *output, size_t output_size, size_t *output_length);

psa_status_t mbedtls_test_opaque_cipher_decrypt(
    const psa_key_attributes_t *attributes,
    const uint8_t *key, size_t key_length,
    psa_algorithm_t alg,
    const uint8_t *input, size_t input_length,
    uint8_t *output, size_t output_size, size_t *output_length);

psa_status_t mbedtls_test_opaque_cipher_encrypt_setup(
    mbedtls_opaque_test_driver_cipher_operation_t *operation,
    const psa_key_attributes_t *attributes,
    const uint8_t *key, size_t key_length,
    psa_algorithm_t alg);

psa_status_t mbedtls_test_opaque_cipher_decrypt_setup(
    mbedtls_opaque_test_driver_cipher_operation_t *operation,
    const psa_key_attributes_t *attributes,
    const uint8_t *key, size_t key_length,
    psa_algorithm_t alg);

psa_status_t mbedtls_test_opaque_cipher_abort(
    mbedtls_opaque_test_driver_cipher_operation_t *operation);

psa_status_t mbedtls_test_opaque_cipher_set_iv(
    mbedtls_opaque_test_driver_cipher_operation_t *operation,
    const uint8_t *iv, size_t iv_length);

psa_status_t mbedtls_test_opaque_cipher_update(
    mbedtls_opaque_test_driver_cipher_operation_t *operation,
    const uint8_t *input, size_t input_length,
    uint8_t *output, size_t output_size, size_t *output_length);

psa_status_t mbedtls_test_opaque_cipher_finish(
    mbedtls_opaque_test_driver_cipher_operation_t *operation,
    uint8_t *output, size_t output_size, size_t *output_length);

#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_TEST_DRIVERS_CIPHER_H */
