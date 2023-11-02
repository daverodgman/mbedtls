/*
 *  PSA crypto client code
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

#include "common.h"
#include "psa/crypto.h"

#if defined(MBEDTLS_PSA_CRYPTO_CLIENT)

#include <string.h>
#include "mbedtls/platform.h"

void psa_reset_key_attributes(psa_key_attributes_t *attributes)
{
    mbedtls_free(attributes->domain_parameters);
    memset(attributes, 0, sizeof(*attributes));
}

psa_status_t psa_set_key_domain_parameters(psa_key_attributes_t *attributes,
                                           psa_key_type_t type,
                                           const uint8_t *data,
                                           size_t data_length)
{
    uint8_t *copy = NULL;

    if (data_length != 0) {
        copy = mbedtls_calloc(1, data_length);
        if (copy == NULL) {
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        }
        memcpy(copy, data, data_length);
    }
    /* After this point, this function is guaranteed to succeed, so it
     * can start modifying `*attributes`. */

    if (attributes->domain_parameters != NULL) {
        mbedtls_free(attributes->domain_parameters);
        attributes->domain_parameters = NULL;
        attributes->domain_parameters_size = 0;
    }

    attributes->domain_parameters = copy;
    attributes->domain_parameters_size = data_length;
    attributes->core.type = type;
    return PSA_SUCCESS;
}

psa_status_t psa_get_key_domain_parameters(
    const psa_key_attributes_t *attributes,
    uint8_t *data, size_t data_size, size_t *data_length)
{
    if (attributes->domain_parameters_size > data_size) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }
    *data_length = attributes->domain_parameters_size;
    if (attributes->domain_parameters_size != 0) {
        memcpy(data, attributes->domain_parameters,
               attributes->domain_parameters_size);
    }
    return PSA_SUCCESS;
}

#endif /* MBEDTLS_PSA_CRYPTO_CLIENT */
