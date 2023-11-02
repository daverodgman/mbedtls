#!/bin/bash -eu

# ssl-opt-in-docker.sh
#
# Purpose
# -------
# This runs ssl-opt.sh in a Docker container.
#
# WARNING: the Dockerfile used by this script is no longer maintained! See
# https://github.com/Mbed-TLS/mbedtls-test/blob/master/README.md#quick-start
# for the set of Docker images we use on the CI.
#
# Notes for users
# ---------------
# If OPENSSL, GNUTLS_CLI, or GNUTLS_SERV are specified, the path must
# correspond to an executable inside the Docker container. The special
# values "next" and "legacy" are also allowed as shorthand for the
# installations inside the container.
#
# See also:
# - scripts/docker_env.sh for general Docker prerequisites and other information.
# - ssl-opt.sh for notes about invocation of that script.

# Copyright The Mbed TLS Contributors
# SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
#
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may
# not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#  http://www.apache.org/licenses/LICENSE-2.0
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

source tests/scripts/docker_env.sh

case "${OPENSSL:-default}" in
    "legacy")  export OPENSSL="/usr/local/openssl-1.0.1j/bin/openssl";;
    "next")    export OPENSSL="/usr/local/openssl-1.1.1a/bin/openssl";;
    *) ;;
esac

case "${GNUTLS_CLI:-default}" in
    "legacy")  export GNUTLS_CLI="/usr/local/gnutls-3.3.8/bin/gnutls-cli";;
    "next")  export GNUTLS_CLI="/usr/local/gnutls-3.7.2/bin/gnutls-cli";;
    *) ;;
esac

case "${GNUTLS_SERV:-default}" in
    "legacy")  export GNUTLS_SERV="/usr/local/gnutls-3.3.8/bin/gnutls-serv";;
    "next")  export GNUTLS_SERV="/usr/local/gnutls-3.7.2/bin/gnutls-serv";;
    *) ;;
esac

run_in_docker \
    -e P_SRV \
    -e P_CLI \
    -e P_PXY \
    -e GNUTLS_CLI \
    -e GNUTLS_SERV \
    -e OPENSSL \
    tests/ssl-opt.sh \
    $@
