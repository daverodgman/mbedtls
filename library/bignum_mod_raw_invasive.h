/**
 * \file bignum_mod_raw_invasive.h
 *
 * \brief Function declarations for invasive functions of Low-level
 *        modular bignum.
 */
/**
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

#ifndef MBEDTLS_BIGNUM_MOD_RAW_INVASIVE_H
#define MBEDTLS_BIGNUM_MOD_RAW_INVASIVE_H

#include "common.h"
#include "mbedtls/bignum.h"
#include "bignum_mod.h"

#if defined(MBEDTLS_TEST_HOOKS)

/** Convert the result of a quasi-reduction to its canonical representative.
 *
 * \param[in,out] X     The address of the MPI to be converted. Must have the
 *                      same number of limbs as \p N. The input value must
 *                      be in range 0 <= X < 2N.
 * \param[in]     N     The address of the modulus.
 */
MBEDTLS_STATIC_TESTABLE
void mbedtls_mpi_mod_raw_fix_quasi_reduction(mbedtls_mpi_uint *X,
                                             const mbedtls_mpi_mod_modulus *N);

#endif /* MBEDTLS_TEST_HOOKS */

#endif /* MBEDTLS_BIGNUM_MOD_RAW_INVASIVE_H */
