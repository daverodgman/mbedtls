/**
 * \file compat-2.x.h
 *
 * \brief Compatibility definitions
 *
 * \deprecated Use the new names directly instead
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

#if defined(MBEDTLS_DEPRECATED_WARNING)
#warning "Including compat-2.x.h is deprecated"
#endif

#ifndef MBEDTLS_COMPAT2X_H
#define MBEDTLS_COMPAT2X_H

/*
 * Macros for renamed functions
 */
#define mbedtls_ctr_drbg_update_ret   mbedtls_ctr_drbg_update
#define mbedtls_hmac_drbg_update_ret  mbedtls_hmac_drbg_update
#define mbedtls_md5_starts_ret        mbedtls_md5_starts
#define mbedtls_md5_update_ret        mbedtls_md5_update
#define mbedtls_md5_finish_ret        mbedtls_md5_finish
#define mbedtls_md5_ret               mbedtls_md5
#define mbedtls_ripemd160_starts_ret  mbedtls_ripemd160_starts
#define mbedtls_ripemd160_update_ret  mbedtls_ripemd160_update
#define mbedtls_ripemd160_finish_ret  mbedtls_ripemd160_finish
#define mbedtls_ripemd160_ret         mbedtls_ripemd160
#define mbedtls_sha1_starts_ret       mbedtls_sha1_starts
#define mbedtls_sha1_update_ret       mbedtls_sha1_update
#define mbedtls_sha1_finish_ret       mbedtls_sha1_finish
#define mbedtls_sha1_ret              mbedtls_sha1
#define mbedtls_sha256_starts_ret     mbedtls_sha256_starts
#define mbedtls_sha256_update_ret     mbedtls_sha256_update
#define mbedtls_sha256_finish_ret     mbedtls_sha256_finish
#define mbedtls_sha256_ret            mbedtls_sha256
#define mbedtls_sha512_starts_ret     mbedtls_sha512_starts
#define mbedtls_sha512_update_ret     mbedtls_sha512_update
#define mbedtls_sha512_finish_ret     mbedtls_sha512_finish
#define mbedtls_sha512_ret            mbedtls_sha512

#endif /* MBEDTLS_COMPAT2X_H */
