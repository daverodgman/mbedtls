#!/bin/sh

# Run the shared library dynamic loading demo program.
# This is only expected to work when Mbed TLS is built as a shared library.

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

set -e -u

program_name="dlopen"
program_dir="${0%/*}"
program="$program_dir/$program_name"

if [ ! -e "$program" ]; then
    # Look for programs in the current directory and the directories above it
    for dir in "." ".." "../.."; do
        program_dir="$dir/programs/test"
        program="$program_dir/$program_name"
        if [ -e "$program" ]; then
            break
        fi
    done
    if [ ! -e "$program" ]; then
        echo "Could not find $program_name program"

        echo "Make sure that Mbed TLS is built as a shared library." \
             "If building out-of-tree, this script must be run" \
             "from the project build directory."
        exit 1
    fi
fi

top_dir="$program_dir/../.."
library_dir="$top_dir/library"

# ELF-based Unix-like (Linux, *BSD, Solaris, ...)
if [ -n "${LD_LIBRARY_PATH-}" ]; then
    LD_LIBRARY_PATH="$library_dir:$LD_LIBRARY_PATH"
else
    LD_LIBRARY_PATH="$library_dir"
fi
export LD_LIBRARY_PATH

# OSX/macOS
if [ -n "${DYLD_LIBRARY_PATH-}" ]; then
    DYLD_LIBRARY_PATH="$library_dir:$DYLD_LIBRARY_PATH"
else
    DYLD_LIBRARY_PATH="$library_dir"
fi
export DYLD_LIBRARY_PATH

echo "Running dynamic loading test program: $program"
echo "Loading libraries from: $library_dir"
"$program"
