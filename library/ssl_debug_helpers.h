/**
 * \file ssl_debug_helpers.h
 *
 * \brief Automatically generated helper functions for debugging
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

#ifndef MBEDTLS_SSL_DEBUG_HELPERS_H
#define MBEDTLS_SSL_DEBUG_HELPERS_H

#include "common.h"

#if defined(MBEDTLS_DEBUG_C)

#include "mbedtls/ssl.h"
#include "ssl_misc.h"


const char *mbedtls_ssl_states_str(mbedtls_ssl_states in);

const char *mbedtls_ssl_protocol_version_str(mbedtls_ssl_protocol_version in);

const char *mbedtls_tls_prf_types_str(mbedtls_tls_prf_types in);

const char *mbedtls_ssl_key_export_type_str(mbedtls_ssl_key_export_type in);

const char *mbedtls_ssl_sig_alg_to_str(uint16_t in);

const char *mbedtls_ssl_named_group_to_str(uint16_t in);

const char *mbedtls_ssl_get_extension_name(unsigned int extension_type);

void mbedtls_ssl_print_extensions(const mbedtls_ssl_context *ssl,
                                  int level, const char *file, int line,
                                  int hs_msg_type, uint32_t extensions_mask,
                                  const char *extra);

void mbedtls_ssl_print_extension(const mbedtls_ssl_context *ssl,
                                 int level, const char *file, int line,
                                 int hs_msg_type, unsigned int extension_type,
                                 const char *extra_msg0, const char *extra_msg1);

#if defined(MBEDTLS_SSL_PROTO_TLS1_3) && defined(MBEDTLS_SSL_SESSION_TICKETS)
void mbedtls_ssl_print_ticket_flags(const mbedtls_ssl_context *ssl,
                                    int level, const char *file, int line,
                                    unsigned int flags);
#endif /* MBEDTLS_SSL_PROTO_TLS1_3 && MBEDTLS_SSL_SESSION_TICKETS */

#define MBEDTLS_SSL_PRINT_EXTS(level, hs_msg_type, extensions_mask)            \
    mbedtls_ssl_print_extensions(ssl, level, __FILE__, __LINE__,       \
                                 hs_msg_type, extensions_mask, NULL)

#define MBEDTLS_SSL_PRINT_EXT(level, hs_msg_type, extension_type, extra)      \
    mbedtls_ssl_print_extension(ssl, level, __FILE__, __LINE__,        \
                                hs_msg_type, extension_type,           \
                                extra, NULL)

#if defined(MBEDTLS_SSL_PROTO_TLS1_3) && defined(MBEDTLS_SSL_SESSION_TICKETS)
#define MBEDTLS_SSL_PRINT_TICKET_FLAGS(level, flags)             \
    mbedtls_ssl_print_ticket_flags(ssl, level, __FILE__, __LINE__, flags)
#endif

#else

#define MBEDTLS_SSL_PRINT_EXTS(level, hs_msg_type, extension_mask)

#define MBEDTLS_SSL_PRINT_EXT(level, hs_msg_type, extension_type, extra)

#if defined(MBEDTLS_SSL_PROTO_TLS1_3) && defined(MBEDTLS_SSL_SESSION_TICKETS)
#define MBEDTLS_SSL_PRINT_TICKET_FLAGS(level, flags)
#endif

#endif /* MBEDTLS_DEBUG_C */

#endif /* MBEDTLS_SSL_DEBUG_HELPERS_H */
