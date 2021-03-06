/*
BSD 3-Clause License

Copyright (c) 2017, Fan Chunquan HSMO
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * The header file for fmock lib.
 *
 *---------------------------------------------------------------------------
 *| VERSION | AUTHOR        | DATE       | NOTE                             |
 *---------------------------------------------------------------------------
 *| 01      | Fan Chunquan  | 2017-05-07 | Creation                         |
 *---------------------------------------------------------------------------
 *| 02      | Fan Chunquan  | 2017-07-16 | Support void function mock with  |
 *|         |               |            |  FMOCK_DECLARE_MOCK_V            |
 *---------------------------------------------------------------------------
 *| 03      | Fan Chunquan  | 2017-12-09 | Support generic type parameters  |
 *---------------------------------------------------------------------------
 */

#ifndef FMOCK_FMOCK_H_
#define FMOCK_FMOCK_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <fmock/fmockcommon.h>
#include <fmock/fmockfuncproto.h>
#include <fmock/fmockexpect.h>
#include <fmock/fmockreturn.h>
#include <fmock/fmocktest.h>

extern void __fmock_init();
#define FMOCK_INIT __fmock_init();

extern int __fmock_use_mock(char* fname, char* argDefinition, char returnType);
extern int __fmock_end_use_mock(char* fname);

#define FMOCK_USE_MOCK(fname,argdefn,returntype) __fmock_use_mock(#fname,argdefn,returntype)

#define FMOCK_END_USE_MOCK(fname) \
	do { \
		__fmock_end_use_mock(#fname); \
	}while(0)

#define FMOCK_DECLARE_MOCK(fname,rtype,proto,args...) \
	rtype fname(proto) \
	{ \
		rtype r; \
		fmock_return_t data = __fmock(#fname,##args); \
		r = *((rtype*)&(data.value)); \
		return r; \
	}
#define FMOCK_DECLARE_MOCK_V(fname,rtype,proto,args...) \
	rtype fname(proto) \
	{ \
		__fmock(#fname,##args); \
		return; \
	}
#define FMOCK_DECLARE_ANOTHER_MOCK(fname,rtype,proto,args...) \
	rtype __FMOCK_func_##fname(proto) \
	{ \
		rtype r; \
		fmock_return_t data = __fmock(#fname,##args); \
		r = *((rtype*)&(data.value)); \
		return r; \
	}
#define PROTO(...) __VA_ARGS__

#define FMOCK_DECLARE_GENERIC_PARAM_TYPE(type, fmocktype) \
	void* __fmock_parseParam_ ## fmocktype (va_list va) { \
		void * gv = malloc(sizeof(type)); \
		type v = va_arg(va,type); \
		memcpy(gv, &v, sizeof(type)); \
		return gv; \
	} \
	void __fmock_freeData_ ## fmocktype (void* gv) { \
		free(gv); \
	}
#define FMOCK_USE_GENERIC_PARAM_TYPE(fname, index, fmocktype) \
	do { \
		fmock_declareParamParser(#fname, index, __fmock_parseParam_ ## fmocktype); \
		fmock_declareParamFreer(#fname, index, __fmock_freeData_ ## fmocktype); \
	} while(0);

extern fmock_return_t __fmock(char* fname, ...);

#define FMOCK_EXPECT_CALL(fname, args...) \
	do { \
		fmock_data_checker_t __fmock_tmp_params [] = args; \
		fmock_expectCall(#fname, __fmock_tmp_params); \
	} while(0)

#define FMOCK_LET_RETURN_BY_DEFAULT(fname,retValue) fmock_defaultReturnOnCall(#fname,retValue)

#define FMOCK_LET_RETURN(fname,retValue) fmock_returnOnExpectedCall(#fname,retValue)


extern int __fmock_clear();
#define FMOCK_CLEAR \
	do { \
		__fmock_clear(); \
	} while(0);

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* FMOCK_FMOCK_H_ */
