/*
 * Helper functions for tests that use any PSA API.
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

#ifndef PSA_HELPERS_H
#define PSA_HELPERS_H

#if defined(MBEDTLS_PSA_CRYPTO_SPM)
#include "spm/psa_defs.h"
#endif

/** Evaluate an expression and fail the test case if it returns an error.
 *
 * \param expr      The expression to evaluate. This is typically a call
 *                  to a \c psa_xxx function that returns a value of type
 *                  #psa_status_t.
 */
#define PSA_ASSERT(expr) TEST_EQUAL((expr), PSA_SUCCESS)

#endif /* PSA_HELPERS_H */
