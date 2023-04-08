Rem LibAndria version 4
Rem A C-based general purpose utility library.
Rem Copyright (c) 2019 Jared A. Maddox
Rem 
Rem Permission is hereby granted, free of charge, to any person obtaining a copy of
Rem this software and associated documentation files (the "Software"), to deal in
Rem the Software without restriction, including without limitation the rights to
Rem use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
Rem of the Software, and to permit persons to whom the Software is furnished to do
Rem so, subject to the following conditions:
Rem 
Rem This grant of rights is subject to two conditions:
Rem 
Rem The above copyright notice and this permission notice shall be included in all
Rem copies or substantial portions of the Software.
Rem 
Rem And:
Rem 
Rem THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
Rem IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
Rem FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
Rem AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
Rem LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
Rem OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
Rem SOFTWARE.


Rem This is a batch file to ensure that Microsoft's nmake runs the right
Rem  makefile. If using Microsoft tools, then just run this file instead of
Rem  making life hard for yourself.

nmake.exe /F MSnmake.mak
