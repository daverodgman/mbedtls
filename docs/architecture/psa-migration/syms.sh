#!/bin/sh
#
# Copyright The Mbed TLS Contributors
# SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
#
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
#
#
# This program is free software; you can redistribute it and/or modify it under the terms of the
# GNU General Public License as published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
# without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with this program; if
# not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301, USA.
#
# Purpose
#
# Show external links in built libraries (X509 or TLS) or modules. This is
# usually done to list Crypto dependencies or to check modules'
# interdependencies.
#
# Usage:
# - build the library with debug symbols and the config you're interested in
#   (default, full minus MBEDTLS_USE_PSA_CRYPTO, full, etc.)
# - launch this script with 1 or more arguments depending on the analysis' goal:
#     - if only 1 argument is used (which is the name of the used config,
#       ex: full), then the analysis is done on libmbedx509 and libmbedtls
#       libraries by default
#     - if multiple arguments are provided, then modules' names (ex: pk,
#       pkparse, pkwrite, etc) are expected after the 1st one and the analysis
#       will be done on those modules instead of the libraries.

set -eu

# list mbedtls_ symbols of a given type in a static library
syms() {
    TYPE="$1"
    FILE="$2"

    nm "$FILE" | sed -n "s/[0-9a-f ]*${TYPE} \(mbedtls_.*\)/\1/p" | sort -u
}

# Check if the provided name refers to a module or library and return the
# same path with proper extension
get_file_with_extension() {
    BASE=$1
    if [ -f $BASE.o ]; then
        echo $BASE.o
    elif [ -f $BASE.a ]; then
        echo $BASE.a
    fi
}

# create listings for the given library
list() {
    NAME="$1"
    FILE=$(get_file_with_extension "library/${NAME}")
    PREF="${CONFIG}-$NAME"

    syms '[TRrD]' $FILE > ${PREF}-defined
    syms U $FILE > ${PREF}-unresolved

    diff ${PREF}-defined ${PREF}-unresolved \
        | sed -n 's/^> //p' > ${PREF}-external
    sed 's/mbedtls_\([^_]*\).*/\1/' ${PREF}-external \
        | uniq -c | sort -rn > ${PREF}-modules

    rm ${PREF}-defined ${PREF}-unresolved
}

CONFIG="${1:-unknown}"

# List of modules to check is provided as parameters
if [ $# -gt 1 ]; then
    shift 1
    ITEMS_TO_CHECK="$@"
else
    ITEMS_TO_CHECK="libmbedx509 libmbedtls"
fi

for ITEM in $ITEMS_TO_CHECK; do
    list $ITEM
done
