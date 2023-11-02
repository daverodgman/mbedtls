#!/bin/bash

print_usage()
{
    cat <<EOF
Usage: $0 [OPTION]...
Prepare the source tree for a release.

Options:
  -u    Prepare for development (undo the release preparation)
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

if [ $# -ne 0 ] && [ "$1" = "--help" ]; then
    print_usage
    exit
fi

unrelease= # if non-empty, we're in undo-release mode
while getopts u OPTLET; do
    case $OPTLET in
        u) unrelease=1;;
        \?)
            echo 1>&2 "$0: unknown option: -$OPTLET"
            echo 1>&2 "Try '$0 --help' for more information."
            exit 3;;
    esac
done



#### .gitignore processing ####

GITIGNORES=$(find . -name ".gitignore")
for GITIGNORE in $GITIGNORES; do
    if [ -n "$unrelease" ]; then
        sed -i '/###START_COMMENTED_GENERATED_FILES###/,/###END_COMMENTED_GENERATED_FILES###/s/^# //' $GITIGNORE
        sed -i 's/###START_COMMENTED_GENERATED_FILES###/###START_GENERATED_FILES###/' $GITIGNORE
        sed -i 's/###END_COMMENTED_GENERATED_FILES###/###END_GENERATED_FILES###/' $GITIGNORE
    else
        sed -i '/###START_GENERATED_FILES###/,/###END_GENERATED_FILES###/s/^/# /' $GITIGNORE
        sed -i 's/###START_GENERATED_FILES###/###START_COMMENTED_GENERATED_FILES###/' $GITIGNORE
        sed -i 's/###END_GENERATED_FILES###/###END_COMMENTED_GENERATED_FILES###/' $GITIGNORE
    fi
done



#### Build scripts ####

# GEN_FILES defaults on (non-empty) in development, off (empty) in releases
if [ -n "$unrelease" ]; then
    r=' yes'
else
    r=''
fi
sed -i 's/^\(GEN_FILES[ ?:]*=\)\([^#]*\)/\1'"$r/" Makefile */Makefile

# GEN_FILES defaults on in development, off in releases
if [ -n "$unrelease" ]; then
    r='ON'
else
    r='OFF'
fi
sed -i '/[Oo][Ff][Ff] in development/! s/^\( *option *( *GEN_FILES  *"[^"]*"  *\)\([A-Za-z0-9][A-Za-z0-9]*\)/\1'"$r/" CMakeLists.txt
