/*
LibAndria version 4
A C-based general purpose utility library.
Copyright (c) 2025 Jared A. Maddox

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

This grant of rights is subject to two conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

And:

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "../detect.h"

#if LIBANDRIA4_PRIMITIVE_PLATDET_PROC_H
# define LIBANDRIA4_PRIMITIVE_PLATDET_PROC_H
	
	#if LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_GNU )
		/* Supported: */
			/* __GNUC__ : GCC C/C++. */
			
		#if defined( __alpha__ )
		#elif defined( __amd64__ || __amd64 || __x86_64__ || __x86_64 )
			/*
				Memory models:
					__ILP32__ (x32 / ILP32: 64-bit mode, but 32-bit ptrs, longs, & ints)
					__LP64__ (LP64: ptr, long, & long long are 64 bit, int is 32 bit)
			*/
			
		#elif defined( __arc__ )
			/*  */
			
		#elif defined( __AVR_ARCH__ || __AVR_XMEGA__ )
			/* AVR, e.g. ATTiny. */
			
		#elif defined( __arm__ || __thumb__ )
			#if defined( __ARM_ARCH_5T__ )
			#elif defined( __ARM_ARCH_7A__ )
			#else
			#endif
			
		#elif defined( __aarch64__ )
			/* Arm 64 */
			
		#elif defined( __bfin || __BFIN__ )
			/* Blackfin. */
			
		#elif defined( __BPF__ || __bpf__ )
			/* eBPF, used for e.g. programatic filtering. */
			
		#elif defined( __TMS320C6X__ || _TMS320C6X )
			/* Some TI DSPs. */
			
		#elif defined( __convex__ )
			/* Convex computers, probably no reason to support. */
			
		#elif defined( cris || CRIS || GNU_CRIS )
			/* ETRAX CRIS? */
			
		#elif defined( __csky__ || __CSKY__ || __ckcore__ || __CKCORE__ )
			/* C-SKY, seems to be a Chinese derivative of Motorola's M-CORE. */
			
		#elif defined( __epiphany__ )
			/* Epiphany, from Adapteva/Zero ASIC. */
			
		#elif defined( fr30 )
			/* Fujitsu FR-30 */
			
		#elif defined( __frv__ )
			/* Fujitsu FR-V */
			
		#elif defined( __AMDGCN__ )
			/* GraphicsCoreNext, an AMD GPU architecture. */
			#error "LibAndria4 does not support GPU architectures, such as AMD GCN.\n"
			
		#elif defined( __H8300SX__ || __H8300S__ || __H8300H__ )
			/* Renesas H8/300 */
			
		#elif defined( __hppa__ )
			/* HP/PA RISC */
			
		#elif defined( i386 || __i386 || __i386__ )
			/* 32-bit x86 */
			#include "procs/x86.h"
			
		#elif defined( __ia64__ || _IA64 || __IA64__ )
			/* Itanium. */
			
		#elif defined( __iq2000__ )
			/* Vitesse IQ2000 */
			
		#elif defined( __lm32__ )
			/* Lattice Mico32 */
			
		#elif defined( __m32c__ )
			/* R8C/M16C/M32C */
			
		#elif defined( __M32R__ || __m32r__ )
			/* Renesas M32R */
			
		#elif defined( __m68k__ )
			/* 68k */
			
		#elif defined( __mcore__ || __MCORE__ )
			/* Motorola M-CORE */
			
		#elif defined( __MICROBLAZE__ || __microblaze__ )
			/* Microblaze. */
			
		#elif defined( __mips__ || mips || __mips )
			/* MIPS */
			
		#elif defined( __mmix__ || __MMIX__ )
			/* MMIX, Donald Knuth's 64-bit modernized educational processor architecture. */
			
		#elif defined( __mn10300__ || __MN10300__ )
			/* Matsushita MN10300 */
			
		#elif defined( moxie || MOXIE )
			/* Moxie is an open-source soft-core processor. */
			
		#elif defined( __MSP430__ )
			/* TI MSP430 */
			
		#elif defined( __nds32__ || __NDS32__ )
			/* Andes NDS32 */
			
		#elif defined( __CUDA_ARCH__ )
			/* Nvidia PTX */
			#error "LibAndria4 does not support GPU architectures, such as Nvidia PTX.\n"
			
		#elif defined( pdp11 || __pdp11_int || __pdp11_model )
			/* PDP-11 */
			
		#elif defined( \
				__powerpc || __powerpc__ || __powerpc64__ || __POWERPC__ || \
				__ppc__ || __ppc64__ || __PPC__ || __PPC64__ || _ARCH_PPC || _ARCH_PPC64 )
			/* PowerPC */
			
		#elif defined( __PRU__ || __pru__ || __PRU_V3__ )
			/* TI PRU */
			
		#elif defined( __riscv || __riscv_a || __riscv_c )
			/* Risc-V */
			
		#elif defined( __RL78__ )
			/* Renesas RL78 */
			
		#elif defined( __RX__ )
			/* Renesas RX */
			
		#elif defined( __s390__ || __s390x__ )
			/* SystemZ: IBM System/360 & relatives */
			/* Specifically detects System/390 */
			
		#elif defined( __sh__ )
			/* SuperH: Sega 32x, Saturn, and Dreamcast */
			
		#elif defined( __sparc__ )
			/* SPARC */
			
		#elif defined( xstormy16 )
			/* Xstormy16 */
			
		#elif defined( __v851__ || __v850 || __v850__ )
			/* NEC V850 */
			
		#elif defined( __vax__ )
			/* Digital's VAX. */
			
		#elif defined( __VISIUM__ )
			/* Visium */
			
		#elif defined( __xtensa__ || __XTENSA__ )
			/* Tensilica's Xtensa */
			
		#else
		#endif
		
	#elif LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_LLVM )
		/* Supported: */
			/* __llvm__ and/or __clang__ : LLVM C / Clang. */
		
		??? ;
		
	#elif LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_TCC )
		/* Supported: */
			/* __TINYC__ : Tiny C Compiler. */
		/* Actually, does TCC support the ADVANCED GCC assembly syntax? */
		
		??? ;
		
	#elif LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_MSVC )
		/* Supported: */
			/* _MSC_VER : MSVC. */
		#include "procs/x86.h"
		
		
		
	#elif LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_COMEAU )
		/* __COMO__ : Comeau C++. */
		/* Support for this should eventually be attempted. */
		
		#error "LibAndria4 platformdetect.h doesn't yet support the Comeau C compiler.\n"
		
	#elif LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_DJGPP )
		/*  __DJGPP__ or __GO32__ : DJGPP. For MSDOS. */
		/* Support for this should eventually be attempted. */
		
		#error "LibAndria4 platformdetect.h doesn't yet support the DJGPP compiler.\n"
		
	#elif LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_WATCOM )
		/* __WATCOMC__ : Watcom / OpenWatcom C/C++. */
		
		#error "LibAndria4 platformdetect.h doesn't yet support the Watcom opr OpenWatcom compiler.\n"
		
		
		
	#elif LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_BORLAND )
		/* __TURBOC__ : Borland Turbo C. */
		/* __BORLANDC__ or __CODEGEARC__ : Borland / CodeGear / Embarcadero */
		/*  C++ Builder. Versions have targeted MSWindows, Linux, Solaris, */
		/*  OS X, iOS, and Android. */
		
		#error "LibAndria4 platformdetect.h doesn't yet support this compiler.\n"
		
	#elif LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_DIGIMARS )
		/*  __DMC__ : Digital Mars C, maybe C++. They're the folks that do "D". */
		#include "procs/x86.h"
		
			
	#elif LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_PCC )
		/* __PCC__ : Portable C Compiler. */
		
		#error "LibAndria4 platformdetect.h doesn't yet support this compiler.\n"
		
	#elif LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_LCC )
		/* __LCC__ : LCC. */
		
		#error "LibAndria4 platformdetect.h doesn't yet support this compiler.\n"
		
	#elif LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_SDCC )
		/* SDCC : Small Device C Compiler. */
		
		#error "LibAndria4 platformdetect.h doesn't yet support this compiler.\n"
		
	#elif LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_ACK )
		/* __ACK__ : Amsterdam Compiler Kit. For MINIX, multiple processors. */
		
		#error "LibAndria4 platformdetect.h doesn't yet support this compiler.\n"
		
	#elif LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_BDS )
		/* "Brain Damage Software" C Compiler. */
		
		#error "LibAndria4 platformdetect.h doesn't yet support this compiler.\n"
		
	#elif LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_OPEN64 )
		/* __OPEN64__ or __OPENCC__ : Open64. */
		
		#error "LibAndria4 platformdetect.h doesn't yet support this compiler.\n"
		
	#elif LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_AZTECC )
		/* AZTEC_C or __AZTEC_C__ : Aztec C. For MSDOS, Apple II DOS 3.3 & */
		/*  ProDOS, Commodore 64, early Macs, CP/M-80, Amiga, & Atari ST. */
		
		#error "LibAndria4 platformdetect.h doesn't yet support this compiler.\n"
		
	#elif LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_NORCROFTC )
		/* __CC_NORCROFT : Norcroft C. */
		
		#error "LibAndria4 platformdetect.h doesn't yet support this compiler.\n"
		
	#elif LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_TENDRAC )
		/* __TenDRA__ : TenDRA C/C++. */
		
		#error "LibAndria4 platformdetect.h doesn't yet support this compiler.\n"
		
		
	#else
		
		#error "\n"
		
		/*
		??? (The SourceForge Pre-defined Compiler Macros wiki didn't identify the compiler) :
			Pyramid 9810:
				pyr
			RS/6000: May be a PowerPC variant?
				_IBMR2 (mostly sure this IS a PowerPC variant)
				
				_POWER (so PowerPC, right?)
				
					/ * These seem to just be early PowerPC versions. * /
				_ARCH_PWR
				_ARCH_PWR2
				_ARCH_PWR3
				_ARCH_PWR4
			TMS470:
				__TMS470__
		*/
		/*
		MinGW32:
			x86:
				_X86_
		DEC D:
			alpha:
				__alpha
		MSVC:
			alpha:
				_M_ALPHA
			amd-64:
				_M_X64 (real or not?)
				_M_AMD64
			arm:
				_M_ARM
				_M_ARMT (Thumb mode)
			x86:
				_M_I86 (16 bit only)
				_M_IX86 (32 bit only)
			Itanium (64 bit):
				_M_IA64
			PowerPC:
				_M_PPC
		Sun Studio:
			amd-64:
				__amd64__
				__amd64
				__x86_64__
				__x86_64
				_ILP32 (x32 / ILP32: 64-bit mode, but 32-bit ptrs, longs, & ints)
				_LP64 (LP64: ptr, long, & long long are 64 bit, int is 32 bit)
			x86:
				__i386
			SPARC:
				__sparc
		HP aCC:
			amd-64:
				_ILP32 (x32 / ILP32: 64-bit mode, but 32-bit ptrs, longs, & ints)
				_LP64 (LP64: ptr, long, & long long are 64 bit, int is 32 bit)
			Itanium (64 bit):
				__ia64
		RealView:
			arm:
				__arm__
				__thumb__ (Thumb mode)
				__TARGET_ARCH_ARM
				__TARGET_ARCH_THUMB
		ImageCraft C
			arm:
				_ARM
		Diab:
			arm:
				__arm
			x86:
				__386
			PowerPC:
				__ppc
		Stratus VOS C:
			HP/PA RISC:
				__HPPA__
			x86: (__VOS__ means big-endian on x86??? What???)
				__i386
				__IA32__
			68k:
				__MC68K__
		Digital Mars:
			x86:
				__I86__
				_M_I86 (16 bit only)
				_M_IX86 (32 bit only)
		Watcom:
			x86:
				__X86__
				_M_IX86
				_M_I86 (16 bit only)
				__386__ (32 bit only?)
				_M_I386 (32 bit only?)
		XL C/C++ :
			x86:
				__THW_INTEL__
			PowerPC:
				_ARCH_PPC
				_ARCH_PPC64
			RS/6000: I'm almost certain this is just an early PowerPC match
				__THW_RS6000
			SystemZ: IBM, supports 60s & 70s System /360 and /370 stuff, often unmodified
				__370__ (System/360)
				__THW_370__ (System/370)
		CodeWarrior:
			x86:
				__INTEL__
			PowerPC:
				__PPCGECKO__ (Gecko, the Nintendo Gamecube & Triforce Arcade Board one)
				__PPCBROADWAY__ (Broadway, the Nintendo Wii one)
		Intel C/C++ :
			Itanium (64 bit):
				_M_IA64
				__itanium__
		SAS/C :
			68k:
				M68000
		MIPSpro:
			MIPS:
				__mips
		Metrowerks:
			MIPS:
				__MIPS__
		Clang:
			SystemZ:
				__zarch__
		Systems/C:
			SystemZ:
				__SYSC_ZARCH__
		*/
		
	#endif
	
#endif /* End primitive platdet proc.h */
