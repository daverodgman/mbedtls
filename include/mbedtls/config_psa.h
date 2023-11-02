/**
 * \file mbedtls/config_psa.h
 * \brief PSA crypto configuration options (set of defines)
 *
 *  This set of compile-time options takes settings defined in
 *  include/mbedtls/mbedtls_config.h and include/psa/crypto_config.h and uses
 *  those definitions to define symbols used in the library code.
 *
 *  Users and integrators should not edit this file, please edit
 *  include/mbedtls/mbedtls_config.h for MBEDTLS_XXX settings or
 *  include/psa/crypto_config.h for PSA_WANT_XXX settings.
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

#ifndef MBEDTLS_CONFIG_PSA_H
#define MBEDTLS_CONFIG_PSA_H

#include "psa/crypto_legacy.h"

#include "psa/crypto_adjust_config_synonyms.h"

#include "mbedtls/config_adjust_psa_superset_legacy.h"

#if defined(MBEDTLS_PSA_CRYPTO_CONFIG)

/* Require built-in implementations based on PSA requirements */

/* We need this to have a complete list of requirements
 * before we deduce what built-ins are required. */
#include "psa/crypto_adjust_config_key_pair_types.h"

#include "mbedtls/config_adjust_legacy_from_psa.h"

#else /* MBEDTLS_PSA_CRYPTO_CONFIG */

/* Infer PSA requirements from Mbed TLS capabilities */

#include "mbedtls/config_adjust_psa_from_legacy.h"

/* Hopefully the file above will have enabled keypair symbols in a consistent
 * way, but including this here fixes them if that wasn't the case. */
#include "psa/crypto_adjust_config_key_pair_types.h"

#endif /* MBEDTLS_PSA_CRYPTO_CONFIG */

#if defined(PSA_WANT_ALG_JPAKE)
#define PSA_WANT_ALG_SOME_PAKE 1
#endif

#include "psa/crypto_adjust_auto_enabled.h"

#endif /* MBEDTLS_CONFIG_PSA_H */
