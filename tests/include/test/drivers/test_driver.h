/*
 * Umbrella include for all of the test driver functionality
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

#ifndef PSA_CRYPTO_TEST_DRIVER_H
#define PSA_CRYPTO_TEST_DRIVER_H

#if defined(PSA_CRYPTO_DRIVER_TEST)
#ifndef PSA_CRYPTO_DRIVER_PRESENT
#define PSA_CRYPTO_DRIVER_PRESENT
#endif
#ifndef PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT
#define PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT
#endif

#define PSA_CRYPTO_TEST_DRIVER_LOCATION 0x7fffff

#include "test/drivers/aead.h"
#include "test/drivers/cipher.h"
#include "test/drivers/hash.h"
#include "test/drivers/mac.h"
#include "test/drivers/key_management.h"
#include "test/drivers/signature.h"
#include "test/drivers/asymmetric_encryption.h"
#include "test/drivers/key_agreement.h"
#include "test/drivers/pake.h"

#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_TEST_DRIVER_H */
