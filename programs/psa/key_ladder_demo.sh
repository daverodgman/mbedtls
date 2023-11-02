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

set -e -u

program_name="key_ladder_demo"
program="${0%/*}/$program_name"
files_to_clean=

if [ ! -e "$program" ]; then
    # Look for programs in the current directory and the directories above it
    for dir in "." ".." "../.."; do
        program="$dir/programs/psa/$program_name"
        if [ -e "$program" ]; then
            break
        fi
    done
    if [ ! -e "$program" ]; then
        echo "Could not find $program_name executable"

        echo "If building out-of-tree, this script must be run" \
             "from the project build directory."
        exit 1
    fi
fi

run () {
    echo
    echo "# $1"
    shift
    echo "+ $*"
    "$@"
}

if [ -e master.key ]; then
    echo "# Reusing the existing master.key file."
else
    files_to_clean="$files_to_clean master.key"
    run "Generate a master key." \
        "$program" generate master=master.key
fi

files_to_clean="$files_to_clean input.txt hello_world.wrap"
echo "Here is some input. See it wrapped." >input.txt
run "Derive a key and wrap some data with it." \
    "$program" wrap master=master.key label=hello label=world \
               input=input.txt output=hello_world.wrap

files_to_clean="$files_to_clean hello_world.txt"
run "Derive the same key again and unwrap the data." \
    "$program" unwrap master=master.key label=hello label=world \
               input=hello_world.wrap output=hello_world.txt
run "Compare the unwrapped data with the original input." \
    cmp input.txt hello_world.txt

files_to_clean="$files_to_clean hellow_orld.txt"
! run "Derive a different key and attempt to unwrap the data. This must fail." \
  "$program" unwrap master=master.key input=hello_world.wrap output=hellow_orld.txt label=hellow label=orld

files_to_clean="$files_to_clean hello.key"
run "Save the first step of the key ladder, then load it as a master key and construct the rest of the ladder." \
    "$program" save master=master.key label=hello \
               input=hello_world.wrap output=hello.key
run "Check that we get the same key by unwrapping data made by the other key." \
    "$program" unwrap master=hello.key label=world \
               input=hello_world.wrap output=hello_world.txt

# Cleanup
rm -f $files_to_clean
