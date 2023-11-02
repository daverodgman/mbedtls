#!/bin/sh

help () {
    cat <<EOF
Usage: $0 [-r]
Collect coverage statistics of library code into an HTML report.

General instructions:
1. Build the library with CFLAGS="--coverage -O0 -g3" and link the test
   programs with LDFLAGS="--coverage".
   This can be an out-of-tree build.
   For example (in-tree):
        make CFLAGS="--coverage -O0 -g3" LDFLAGS="--coverage"
   Or (out-of-tree):
        mkdir build-coverage && cd build-coverage &&
        cmake -D CMAKE_BUILD_TYPE=Coverage .. && make
2. Run whatever tests you want.
3. Run this script from the parent of the directory containing the library
   object files and coverage statistics files.
4. Browse the coverage report in Coverage/index.html.
5. After rework, run "$0 -r", then re-test and run "$0" to get a fresh report.

Options
  -r    Reset traces. Run this before re-testing to get fresh measurements.
EOF
}

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

set -eu

# Collect stats and build a HTML report.
lcov_library_report () {
    rm -rf Coverage
    mkdir Coverage Coverage/tmp
    lcov --capture --initial --directory library -o Coverage/tmp/files.info
    lcov --rc lcov_branch_coverage=1 --capture --directory library -o Coverage/tmp/tests.info
    lcov --rc lcov_branch_coverage=1 --add-tracefile Coverage/tmp/files.info --add-tracefile Coverage/tmp/tests.info -o Coverage/tmp/all.info
    lcov --rc lcov_branch_coverage=1 --remove Coverage/tmp/all.info -o Coverage/tmp/final.info '*.h'
    gendesc tests/Descriptions.txt -o Coverage/tmp/descriptions
    genhtml --title "Mbed TLS" --description-file Coverage/tmp/descriptions --keep-descriptions --legend --branch-coverage -o Coverage Coverage/tmp/final.info
    rm -f Coverage/tmp/*.info Coverage/tmp/descriptions
    echo "Coverage report in: Coverage/index.html"
}

# Reset the traces to 0.
lcov_reset_traces () {
    # Location with plain make
    rm -f library/*.gcda
    # Location with CMake
    rm -f library/CMakeFiles/*.dir/*.gcda
}

if [ $# -gt 0 ] && [ "$1" = "--help" ]; then
    help
    exit
fi

main=lcov_library_report
while getopts r OPTLET; do
    case $OPTLET in
        r) main=lcov_reset_traces;;
        *) help 2>&1; exit 120;;
    esac
done
shift $((OPTIND - 1))

"$main" "$@"
