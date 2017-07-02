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

#include <fmock/fmock.h>
#include "fmockimpl_calllog.h"
#include "fmockimpl_result.h"
#include "fmockimpl_data.h"
#include <stdlib.h>
#include <string.h>

static int fmock_runSumSearchByFunc_cmp(void * node, void * compValue)
{
	fmock_funcRunSum_t* pRun = (fmock_funcRunSum_t*) node;
	char* fname = (char*) compValue;
	return strcmp(pRun->fname, fname);
}
fmock_funcRunSum_t* fmock_searchRunSumByFunc(char* fname)
{
	return (fmock_funcRunSum_t*) fmock_list_search(&fmock_gFuncRunSummaries,
			fmock_runSumSearchByFunc_cmp, fname);
}

void fmock_initRunSumByFunc(char* fname)
{
	if (fmock_searchRunSumByFunc(fname))
		fmock_clearRunSumByFunc(fname);
	fmock_funcRunSum_t* pRun = (fmock_funcRunSum_t*) malloc(
			sizeof(fmock_funcRunSum_t));
	memset(pRun, 0, sizeof(fmock_funcRunSum_t));
	pRun->fname = (char*) malloc(strlen(fname) + 1);
	strcpy(pRun->fname, fname);
	pRun->result = FMOCK_PASS;
	pRun->unexpected = 0;
	fmock_list_init(&pRun->statistics);
	fmock_list_append(&fmock_gFuncRunSummaries, pRun);
}

void fmock_clearRunSumByFunc(char* fname)
{
	fmock_funcRunSum_t* pRun = fmock_searchRunSumByFunc(fname);
	if (!pRun)
		return;
	for (; pRun->statistics.head;)
	{
		fmock_mockCalled_t* pCalled =
				(fmock_mockCalled_t*) pRun->statistics.head;
		fmock_list_remove(&pRun->statistics, pCalled);
		free(pCalled);
	}
	free(pRun->fname);
	fmock_list_remove(&fmock_gFuncRunSummaries, pRun);
}

void fmock_freeRunSum(void* data)
{
	fmock_funcRunSum_t* pRun = (fmock_funcRunSum_t*)data;
	if(!pRun)
		return;
	fmock_list_clear(&pRun->statistics, free);
	free(pRun->fname);
}
void fmock_clearRunSums()
{
	fmock_list_clear(&fmock_gFuncRunSummaries,fmock_freeRunSum);
}

static int fmock_mockCalledCaseSearchByExpect_cmp(void * node, void * compValue)
{
	fmock_mockCalled_t* pCall = (fmock_mockCalled_t*) node;
	fmock_expectCall_t* pExp = (fmock_expectCall_t*) compValue;
	if (pCall->expect == pExp)
		return 0;
	else
		return 1;
}
fmock_mockCalled_t* fmock_recordCallStatisticByExpect(
		fmock_funcRunSum_t* pRunSum, fmock_expectCall_t* pExp)
{
	fmock_mockCalled_t* pCall = (fmock_mockCalled_t*) fmock_list_search(
			&pRunSum->statistics, fmock_mockCalledCaseSearchByExpect_cmp, pExp);
	if (!pCall)
	{
		pCall = (fmock_mockCalled_t*) malloc(sizeof(fmock_mockCalled_t));
		memset(pCall, 0, sizeof(fmock_mockCalled_t));
		pCall->expect = pExp;
		pCall->times = 0;
	}
	pCall->times++;
	return pCall;
}

