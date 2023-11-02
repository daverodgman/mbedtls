/** \file asn1_helpers.c
 *
 * \brief Helper functions for tests that manipulate ASN.1 data.
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

#include <test/helpers.h>
#include <test/macros.h>

#if defined(MBEDTLS_ASN1_PARSE_C)

#include <mbedtls/asn1.h>

int mbedtls_test_asn1_skip_integer(unsigned char **p, const unsigned char *end,
                                   size_t min_bits, size_t max_bits,
                                   int must_be_odd)
{
    size_t len;
    size_t actual_bits;
    unsigned char msb;
    TEST_EQUAL(mbedtls_asn1_get_tag(p, end, &len,
                                    MBEDTLS_ASN1_INTEGER),
               0);

    /* Check if the retrieved length doesn't extend the actual buffer's size.
     * It is assumed here, that end >= p, which validates casting to size_t. */
    TEST_ASSERT(len <= (size_t) (end - *p));

    /* Tolerate a slight departure from DER encoding:
     * - 0 may be represented by an empty string or a 1-byte string.
     * - The sign bit may be used as a value bit. */
    if ((len == 1 && (*p)[0] == 0) ||
        (len > 1 && (*p)[0] == 0 && ((*p)[1] & 0x80) != 0)) {
        ++(*p);
        --len;
    }
    if (min_bits == 0 && len == 0) {
        return 1;
    }
    msb = (*p)[0];
    TEST_ASSERT(msb != 0);
    actual_bits = 8 * (len - 1);
    while (msb != 0) {
        msb >>= 1;
        ++actual_bits;
    }
    TEST_ASSERT(actual_bits >= min_bits);
    TEST_ASSERT(actual_bits <= max_bits);
    if (must_be_odd) {
        TEST_ASSERT(((*p)[len-1] & 1) != 0);
    }
    *p += len;
    return 1;
exit:
    return 0;
}

#endif /* MBEDTLS_ASN1_PARSE_C */
