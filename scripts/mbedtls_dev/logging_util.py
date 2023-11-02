"""Auxiliary functions used for logging module.
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

import logging
import sys

def configure_logger(
        logger: logging.Logger,
        log_format="[%(levelname)s]: %(message)s",
        split_level=logging.WARNING
    ) -> None:
    """
    Configure the logging.Logger instance so that:
        - Format is set to any log_format.
            Default: "[%(levelname)s]: %(message)s"
        - loglevel >= split_level are printed to stderr.
        - loglevel <  split_level are printed to stdout.
            Default: logging.WARNING
    """
    class MaxLevelFilter(logging.Filter):
        # pylint: disable=too-few-public-methods
        def __init__(self, max_level, name=''):
            super().__init__(name)
            self.max_level = max_level

        def filter(self, record: logging.LogRecord) -> bool:
            return record.levelno <= self.max_level

    log_formatter = logging.Formatter(log_format)

    # set loglevel >= split_level to be printed to stderr
    stderr_hdlr = logging.StreamHandler(sys.stderr)
    stderr_hdlr.setLevel(split_level)
    stderr_hdlr.setFormatter(log_formatter)

    # set loglevel < split_level to be printed to stdout
    stdout_hdlr = logging.StreamHandler(sys.stdout)
    stdout_hdlr.addFilter(MaxLevelFilter(split_level - 1))
    stdout_hdlr.setFormatter(log_formatter)

    logger.addHandler(stderr_hdlr)
    logger.addHandler(stdout_hdlr)
