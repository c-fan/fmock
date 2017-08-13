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
 *---------------------------------------------------------------------------
 *| VERSION	| AUTHOR		| DATE			| NOTE							|
 *---------------------------------------------------------------------------
 *| 01		| Fan Chunquan	| 2017-05-20	| Creation						|
 *---------------------------------------------------------------------------
 */

#ifndef FMOCK_FMOCKIMPL_FUNCSPEC_H_
#define FMOCK_FMOCKIMPL_FUNCSPEC_H_

#include <fmock/fmockcommon.h>

/**
 * function prototype
 */
typedef struct
{
	fmock_list_node_t listNode;
	int index; /* which parameter... NOTE - index starting from 0. */
	fmock_type_t paramType;
} fmock_param_type_t;
typedef fmock_list_t fmock_param_spec_t;

typedef struct
{
	fmock_type_t returnType; /* return type */
	int paramNum; /* number of parameters */
	fmock_param_spec_t paramSpec; /* parameters type */
} fmock_func_spec_t;

typedef struct
{
	fmock_list_node_t listNode;
	char* fname;
	char* argdefn; /* arguments definition */
	fmock_func_spec_t spec;
} fmock_func_t;
typedef fmock_list_t fmock_func_list_t;

extern fmock_func_t* fmock_searchFuncByName(char* fname);
extern int fmock_initFunctionSpec(char* funcName, char* argDefinition,
		char returnType);
extern int fmock_clearFunctionSpec(char* fname);
extern void fmock_clearAllFunctionSpecs();

#endif /* FMOCK_FMOCKIMPL_FUNCSPEC_H_ */
