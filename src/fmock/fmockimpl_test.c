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

#include "fmockimpl_data.h"

void __fmock_init()
{
	fmock_gTestName = FMOCK_NULL;
	fmock_list_init(&fmock_gFunctionMocks);
	fmock_list_init(&fmock_gExpects);
	fmock_list_init(&fmock_gFuncReturns);
	fmock_list_init(&fmock_gCallLog);
	fmock_list_init(&fmock_gFuncRunSummaries);
	fmock_list_init(&fmock_gUnexpectedRecords);
}

int __fmock_clear()
{
	if (fmock_gExpects.size > 0 || fmock_gFuncReturns.size > 0
			|| fmock_gFuncRunSummaries.size > 0 || fmock_gCallLog.size > 0)
		return FMOCK_ERROR;
	fmock_clearAllFunctionSpecs();
	return FMOCK_OK;
}

int __fmock_start_test(char* tid)
{
	if (fmock_gTestName)
	{
		return FMOCK_ERROR; // old test data not yet clean up
	}
	fmock_gTestName = (char*) malloc(strlen(tid) + 1);
	strcpy(fmock_gTestName, tid);
	fmock_initResult(tid);
	return FMOCK_OK;
}

int __fmock_use_mock(char* fname, char* argDefinition, char returnType)
{
	// initialize mock according to defined, and add it to the mock list
	// TODO? may separate function specification from adding functions to test mock list
	if (fmock_initFunctionSpec(fname, argDefinition, returnType) == FMOCK_ERROR)
	{
		return FMOCK_ERROR;
	}
	// initialize data for this mock
	fmock_initExpectByFunc(fname);
	fmock_initReturnSpecByFunc(fname);
	fmock_initRunSumByFunc(fname);
	return FMOCK_OK;
}

int __fmock_end_use_mock(char* fname)
{
	return fmock_clearFunctionSpec(fname);
}

void __fmock_clear_test_data(char* tname)
{
	if(strcmp(fmock_gTestName,tname)!=0)
	{
		return;// FMOCK_ERROR;
	}
	fmock_clearCallLog();
	fmock_clearExpects();
	fmock_clearReturnSpecs();
	fmock_clearRunSums();
}
void __fmock_clear_test_result(char* tname)
{
	fmock_clearResult(tname);
	fmock_clearUnexpectedCallRecords();
	free(fmock_gTestName);
}

