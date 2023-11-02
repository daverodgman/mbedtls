/*
 *  Classic "Hello, world" demonstration program
 *
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

#include "mbedtls/build_info.h"

#include "mbedtls/platform.h"

#if defined(MBEDTLS_MD5_C)
#include "mbedtls/md5.h"
#endif

#if !defined(MBEDTLS_MD5_C)
int main(void)
{
    mbedtls_printf("MBEDTLS_MD5_C not defined.\n");
    mbedtls_exit(0);
}
#else


int main(void)
{
    int i, ret;
    unsigned char digest[16];
    char str[] = "Hello, world!";

    mbedtls_printf("\n  MD5('%s') = ", str);

    if ((ret = mbedtls_md5((unsigned char *) str, 13, digest)) != 0) {
        mbedtls_exit(MBEDTLS_EXIT_FAILURE);
    }

    for (i = 0; i < 16; i++) {
        mbedtls_printf("%02x", digest[i]);
    }

    mbedtls_printf("\n\n");

    mbedtls_exit(MBEDTLS_EXIT_SUCCESS);
}
#endif /* MBEDTLS_MD5_C */
