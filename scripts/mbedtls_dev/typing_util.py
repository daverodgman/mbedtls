"""Auxiliary definitions used in type annotations.
"""

# Copyright The Mbed TLS Contributors
# SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 *
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may
# not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
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

from typing import Any

# The typing_extensions module is necessary for type annotations that are
# checked with mypy. It is only used for type annotations or to define
# things that are themselves only used for type annotations. It is not
# available on a default Python installation. Therefore, try loading
# what we need from it for the sake of mypy (which depends on, or comes
# with, typing_extensions), and if not define substitutes that lack the
# static type information but are good enough at runtime.
try:
    from typing_extensions import Protocol #pylint: disable=import-error
except ImportError:
    class Protocol: #type: ignore
        #pylint: disable=too-few-public-methods
        pass

class Writable(Protocol):
    """Abstract class for typing hints."""
    # pylint: disable=no-self-use,too-few-public-methods,unused-argument
    def write(self, text: str) -> Any:
        ...
