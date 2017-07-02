//BSD 3-Clause License
//
//Copyright (c) 2017, Fan Chunquan HSMO
//All rights reserved.
//
//Redistribution and use in source and binary forms, with or without
//modification, are permitted provided that the following conditions are met:
//
//* Redistributions of source code must retain the above copyright notice, this
//  list of conditions and the following disclaimer.
//
//* Redistributions in binary form must reproduce the above copyright notice,
//  this list of conditions and the following disclaimer in the documentation
//  and/or other materials provided with the distribution.
//
//* Neither the name of the copyright holder nor the names of its
//  contributors may be used to endorse or promote products derived from
//  this software without specific prior written permission.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
//FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
//CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
//OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

/*
 *---------------------------------------------------------------------------
 *| VERSION	| AUTHOR		| DATE			| NOTE							|
 *---------------------------------------------------------------------------
 *| 01		| Fan Chunquan	| 2017-05-28	| Creation						|
 *---------------------------------------------------------------------------
 */

#ifndef FMOCK_FMOCKIMPL_CALLLOG_H_
#define FMOCK_FMOCKIMPL_CALLLOG_H_

#include <time.h>
#include "fmockimpl_expect.h"

/*
 * record actual calls to function
 */
typedef struct
{
	fmock_list_node_t listNode;
	fmock_data_t param;
} fmock_calledParam_t;
typedef fmock_list_t fmock_calledParams_t;
typedef struct
{
	fmock_list_node_t listNode;
	time_t time;
	char* fname; // function name
	fmock_calledParams_t params;	// actual parameters passed
	fmock_expectCall_t* matchedExpect;
	fmock_data_t retValue;	// value returned
	char** callStack; // call stack info
	int callStackSize; // call stack size
} fmock_call_t;
typedef fmock_list_t fmock_callLog_t;

extern void fmock_recordUnexpectedCall(fmock_call_t* pUnexpectedCall);

extern void fmock_clearCallLog();
extern void fmock_clearUnexpectedCallRecords();

#endif /* FMOCK_FMOCKIMPL_CALLLOG_H_ */
