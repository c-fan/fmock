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
 *| 01		| Fan Chunquan	| 2017-05-20	| Creation						|
 *---------------------------------------------------------------------------
 */

#ifndef FMOCK_FMOCKIMPL_DATA_H_
#define FMOCK_FMOCKIMPL_DATA_H_

#include "fmockimpl_funcspec.h"
#include "fmockimpl_expect.h"
#include "fmockimpl_return.h"
#include "fmockimpl_funcrunsum.h"
#include "fmockimpl_calllog.h"
#include "fmockimpl_result.h"
#include <fmock/fmocktest.h>

char* fmock_gTestName;

/*
 * function mocks involved in test
 */
fmock_func_list_t fmock_gFunctionMocks;

/*
 * mock call expects
 */
fmock_expects_t fmock_gExpects;

/*
 * mock returns specified
 */
fmock_returnSpec_list_t fmock_gFuncReturns;

/*
 * call log (execution log)
 */
fmock_callLog_t fmock_gCallLog;

/*
 * execution summary per each function mock
 */
fmock_funcRunSum_list_t fmock_gFuncRunSummaries;

/*
 * result
 */
fmock_result_t fmock_gResult;
fmock_unexpectedCallRecord_list_t fmock_gUnexpectedRecords;
//
//extern int __init_mock_data(char* fname);
//extern int __clear_mock_data(char* fname);

#endif /* FMOCK_FMOCKIMPL_DATA_H_ */
