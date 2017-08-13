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

#ifndef FMOCK_FMOCKIMPL_RETURN_H_
#define FMOCK_FMOCKIMPL_RETURN_H_

#include <fmock/fmockcommon.h>
#include "fmockimpl_expect.h"

typedef struct
{
	fmock_list_node_t listNode;
	fmock_expectCall_t* call; /* if NULL (0), means default return value */
	fmock_data_t retValue; /* return value */
} fmock_returnOnCall_t;
typedef fmock_list_t fmock_returnOnCall_list_t;

typedef struct
{
	fmock_list_node_t listNode;
	char* fname;
	fmock_returnOnCall_list_t retSpec;
} fmock_returnSpec_t;

typedef fmock_list_t fmock_returnSpec_list_t;

extern fmock_returnSpec_t* fmock_searchReturnSpecsByFunc(char* fname);

extern fmock_data_t fmock_getReturnValueOnCall(char* fname,
		fmock_expectCall_t* call);

extern fmock_returnOnCall_t* fmock_getReturnSpecOnCall(char* fname,
		fmock_expectCall_t* call);

extern fmock_data_t fmock_getDefaultReturnValue(char* fname);

extern void fmock_initReturnSpecByFunc(char* fname);
extern void fmock_clearReturnSpecsByFunc(char* fname);
extern void fmock_clearReturnSpecs();

#endif /* FMOCK_FMOCKIMPL_RETURN_H_ */
