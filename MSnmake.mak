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


# The Microsoft nmake localizer for makefiles.

# This is essentially unfilled, and I'm not even sure nmake defaults to it. Most
#  of the interesting stuff is called "Preprocessing" by Microsoft, and their
#  docs aren't the best things in the world, but there are several useful things
#  that they describe.

# Supposing that the exit code of a program needs to be provided to IF, enclose
#  the command in square brackets, bearing in mind that the usual macro
#  expansions will happen, and nmake will do the needed plumbing.
!IF EXIST( overrides/rootoverride.make )
!INCLUDE overrides/rootoverride.make
!ENDIF
