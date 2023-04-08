# LibAndria version 4
# A C-based general purpose utility library.
# Copyright (c) 2019 Jared A. Maddox
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
# of the Software, and to permit persons to whom the Software is furnished to do
# so, subject to the following conditions:
# 
# This grant of rights is subject to two conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# And:
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.


# The GNU make localizer for makefiles.
# To assign only things that haven't already been assigned, use '?=' instead of
#  '='


# The single dot is intentional: we're intentionally just pointing back to the
#  directory this file is in.
basification_path=.
basification_extension=

include buildtools/GNU_make/common.make

# rootoverride isn't guaranteed to exist, but if it does, then it is intended to
#  allow overrides of... STUFF in this file.
-include overrides/rootoverride.make



all: 
	$(make_runfile) Makefile all


build:
	$(make_runfile) Makefile build

build-sourcecheck:
	$(make_runfile) Makefile build-sourcecheck


install: 
	$(make_runfile) Makefile install
# example
# install: default
#         install gcd INSTALL_BIN
#         install libmathlib.a INSTALL_LIB

# Create the directories for installation, but don't fill them
installdir: 
	$(make_runfile) Makefile installdir

uninstall: 
	$(make_runfile) Makefile uninstall


clean: 
	$(make_runfile) Makefile clean

# Clean for distribuition: stricter than just "clean"
distclean: 
	$(make_runfile) Makefile distclean

# Clean up almost everything that can be rebuilt; usually config scripts will be
#  left alone. Some files may require special tools to reconstruct
maintainer-clean: 
	$(make_runfile) Makefile maintainer-clean


# Create a distribution file (e.g. a tar file, perhaps compressed with gzip);
#  the base-most entity in the file should be a directory named after both
#  project and version, which in turn should fully contain the project; the
#  target should depend on all relevant targets, to ensure that everything is
#  "fresh"
dist: 
	$(make_runfile) Makefile dist


# Test the built project: DO NOT depend on installation
check: 
	$(make_runfile) Makefile check

# Test the source files; unit testing
sourcecheck: 
	$(make_runfile) Makefile sourcecheck
