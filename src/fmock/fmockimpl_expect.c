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

#include <fmock/fmockexpect.h>
#include "fmockimpl_expect.h"
#include "fmockimpl_data.h"
#include <stdlib.h>
#include <string.h>

void fmock_initExpectByFunc(char* fname)
{
	fmock_expect_t* pExpect = (fmock_expect_t*) malloc(sizeof(fmock_expect_t));
	memset(pExpect, 0, sizeof(fmock_expect_t));
	pExpect->fname = (char*) malloc(strlen(fname) + 1);
	strcpy(pExpect->fname, fname);
	fmock_list_append(&fmock_gExpects, pExpect);
}

/* search fmock_expect_t by function name */
static int fmock_expect_cmp(void * node, void * compValue)
{
	/* node is fmock_expect_t */
	fmock_expect_t* pExp = (fmock_expect_t*) node;
	char* fname = (char*) compValue;
	return strcmp(pExp->fname, fname);
}

fmock_expect_t* fmock_searchExpectByFunc(char* fname)
{
	return (fmock_expect_t*) fmock_list_search(&fmock_gExpects,
			fmock_expect_cmp, fname);
}

void fmock_clearExpectByFunc(char* fname)
{
	fmock_expect_t* pExpect = fmock_searchExpectByFunc(fname);
	if (!pExpect)
	{
		return;
	}
	for (; pExpect->expectedCalls.head;)
	{
		fmock_expectCall_t* pExpCall =
				(fmock_expectCall_t*) pExpect->expectedCalls.head;
		for (; pExpCall->expectedParams.head;)
		{
			fmock_expectParam_t* pExpParam =
					(fmock_expectParam_t*) pExpCall->expectedParams.head;
			fmock_list_remove(&pExpCall->expectedParams, pExpParam);
			free(pExpParam);
		}
		fmock_list_remove(&pExpect->expectedCalls, pExpCall);
		free(pExpCall);
	}
	fmock_list_remove(&fmock_gExpects, pExpect);
	free(pExpect->fname);
	free(pExpect);
}

static void fmock_freeExpect(void* data)
{
	fmock_expect_t* pExpect = (fmock_expect_t*)data;
	if (!pExpect)
	{
		return;
	}
	for (; pExpect->expectedCalls.head;)
	{
		fmock_expectCall_t* pExpCall =
				(fmock_expectCall_t*) pExpect->expectedCalls.head;
		for (; pExpCall->expectedParams.head;)
		{
			fmock_expectParam_t* pExpParam =
					(fmock_expectParam_t*) pExpCall->expectedParams.head;
			fmock_list_remove(&pExpCall->expectedParams, pExpParam);
			free(pExpParam);
		}
		fmock_list_remove(&pExpect->expectedCalls, pExpCall);
		free(pExpCall);
	}
	fmock_list_remove(&fmock_gExpects, pExpect);
	free(pExpect->fname);
	free(pExpect);
}
void fmock_clearExpects()
{
	fmock_list_clear(&fmock_gExpects, fmock_freeExpect);
}

int fmock_expectCall(char* fname, fmock_data_checker_t checkers[])
{
	fmock_func_t* pFunc = fmock_searchFuncByName(fname);
	fmock_expect_t* pExpect = fmock_searchExpectByFunc(fname);
	if (!pFunc || !pExpect)
	{
		return FMOCK_ERROR;
	}
	fmock_expectCall_t* pExpCall = (fmock_expectCall_t*) malloc(
			sizeof(fmock_expectCall_t));
	memset(pExpCall, 0, sizeof(fmock_expectCall_t));
	fmock_list_init(&pExpCall->expectedParams);
	int paramIndex = 0;
	for (; paramIndex < pFunc->spec.paramNum; paramIndex++)
	{
		fmock_expectParam_t* pExpParam = (fmock_expectParam_t*) malloc(
				sizeof(fmock_expectParam_t));
		memset(pExpParam, 0, sizeof(fmock_expectParam_t));
		pExpParam->index = paramIndex;
		pExpParam->checker = checkers[paramIndex];
		fmock_list_append(&pExpCall->expectedParams, pExpParam);
	}
	fmock_list_append(&pExpect->expectedCalls, pExpCall);
	return FMOCK_OK;
}
