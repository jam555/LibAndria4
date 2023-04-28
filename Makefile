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


# This is the generic root-most makefile.

# Note that includes aren't the same across all makefile styles- in particular,
#  GNU and Microsoft are COMPLETELY incompatible. So, that stuff MUST be handled
#  on the command line. The buildtools/*/common.make files provide variables to
#  handle precisely that.



all: 
	echo "Alert: The all target isn't currently implemented by LibAndria4."

world: all install
# This should probably be followed by using the preprocessor and/or compiler to
#  generate localized support files.


$(BUILDDIR)obj/stdmonads.o: basic/stdmonads.c
	$(compileonlyCcommand) basic/stdmonads.c $@
$(BUILDDIR)obj/stdmem.o: basic/stdmem.c
	$(compileonlyCcommand) basic/stdmem.c $@
	

# There should eventually be a pre-build option, that builds at least the
#  preprocessor from C source to iterate to the self-compiling versions.
build: 
	echo "Alert: The build target isn't currently needed by LibAndria4."

$(BUILDDIR)test/stdmonadstest.o: tests/stdmonadstest.c
	$(compileonlyCcommand) tests/stdmonadstest.c $@
$(BUILDDIR)test/stdmonadstest.exe: $(BUILDDIR)obj/stdmonads.o $(BUILDDIR)test/stdmonadstest.o
	$(genericcompileCcommand) $@ $^
$(BUILDDIR)test/pascalarraytest.exe: tests/pascalarraytest.c $(BUILDDIR)obj/stdmonads.o $(BUILDDIR)obj/stdmem.o
	$(genericcompileCcommand) $@ $^


import:
	echo "Alert: The import target isn't currently needed by LibAndria4."

install: 
	echo "Error: The install target isn't currently implemented by LibAndria4."
# example-
# install: default
#         install gcd INSTALL_BIN
#         install libmathlib.a INSTALL_LIB

# Create the directories for installation, but don't fill them
installdir: 
	echo "Error: The installdir target isn't currently implemented by LibAndria4."

uninstall: 
	echo "Error: The uninstall target isn't currently implemented by LibAndria4."


clean: 
	echo "Error: The clean target isn't currently implemented by LibAndria4."

# Clean for distribuition: stricter than just "clean"
distclean: clean
	echo "Error: The distclean target isn't currently implemented by LibAndria4."
# Then do more stuff, like executables.

# Clean up almost everything that can be rebuilt; usually config scripts will be
#  left alone. Some files may require special tools to reconstruct
maintainer-clean: distclean
	echo "Error: The maintainer-clean target isn't currently implemented by LibAndria4."
# And even more stuff...


# Create a distribution file (e.g. a tar file, perhaps compressed with gzip);
#  the base-most entity in the file should be a directory named after both
#  project and version, which in turn should fully contain the project; the
#  target should depend on all relevant targets, to ensure that everything is
#  "fresh"
dist: build
	echo "Error: The dist target isn't currently implemented by LibAndria4."
# So, how do we build?


# Test the built project: DO NOT depend on installation
check: 
	echo "Alert: The check target isn't currently implemented by LibAndria4."
# Tests.

# Test the source files; unit testing
sourcecheck: stdmonads_test pascalarray_test
# Then run tests.
stdmonads_test: $(BUILDDIR)test/stdmonadstest.exe
	$^
pascalarray_test: $(BUILDDIR)test/pascalarraytest.exe
	$^
