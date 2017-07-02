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

#include "fmockimpl_return.h"
#include "fmockimpl_data.h"
#include <fmock/fmockreturn.h>
#include <stdlib.h>
#include <string.h>

void fmock_initReturnSpecByFunc(char* fname)
{
	fmock_returnSpec_t* pRetSpec = (fmock_returnSpec_t*) malloc(
			sizeof(fmock_returnSpec_t));
	memset(pRetSpec, 0, sizeof(fmock_returnSpec_t));
	pRetSpec->fname = (char*) malloc(strlen(fname) + 1);
	strcpy(pRetSpec->fname, fname);
	fmock_list_init(&pRetSpec->retSpec);
	fmock_list_append(&fmock_gFuncReturns, pRetSpec);
}

static int fmock_returnSpec_cmp(void * node, void * compValue)
{
	fmock_returnSpec_t* pret = (fmock_returnSpec_t*) node;
	char* fname = (char*) compValue;
	return strcmp(pret->fname, fname);
}
fmock_returnSpec_t* fmock_searchReturnSpecsByFunc(char* fname)
{
	return (fmock_returnSpec_t*) fmock_list_search(&fmock_gFuncReturns,
			fmock_returnSpec_cmp, fname);
}

static int fmock_returnExpCall_cmp(void* node, void* cmpValue)
{
	fmock_returnOnCall_t* pRetOnCall = (fmock_returnOnCall_t*) node;
	fmock_expectCall_t* pExpCall = (fmock_expectCall_t*) cmpValue;
	if (pRetOnCall->call == pExpCall)
		return 0;
	else
		return -1;
}
fmock_data_t fmock_getDefaultReturnValue(char* fname)
{
	fmock_data_t retValue; //=0
	fmock_returnSpec_t* pRet = fmock_searchReturnSpecsByFunc(fname);
	fmock_returnOnCall_t* pRetOnCall =
			(fmock_returnOnCall_t*) fmock_list_search(&pRet->retSpec,
					fmock_returnExpCall_cmp, 0);
	if (pRetOnCall)
		retValue = pRetOnCall->retValue;
	return retValue;
}
fmock_returnOnCall_t* fmock_getReturnSpecOnCall(char* fname,
		fmock_expectCall_t* call)
{
	fmock_returnSpec_t* pRet = fmock_searchReturnSpecsByFunc(fname);
	fmock_returnOnCall_t* pRetOnCall =
			(fmock_returnOnCall_t*) fmock_list_search(&pRet->retSpec,
					fmock_returnExpCall_cmp, call);
	return pRetOnCall;
}
fmock_data_t fmock_getReturnValueOnCall(char* fname, fmock_expectCall_t* call)
{
	fmock_returnSpec_t* pRet = fmock_searchReturnSpecsByFunc(fname);
	fmock_returnOnCall_t* pRetOnCall =
			(fmock_returnOnCall_t*) fmock_list_search(&pRet->retSpec,
					fmock_returnExpCall_cmp, call);
	if (pRetOnCall)
		return pRetOnCall->retValue;
	else
		return fmock_getDefaultReturnValue(fname);
}

void fmock_clearReturnSpecsByFunc(char* fname)
{
	fmock_returnSpec_t* pRetSpec = fmock_searchReturnSpecsByFunc(fname);
	for (; pRetSpec->retSpec.head;)
	{
		fmock_returnOnCall_t* pRetOnCall =
				(fmock_returnOnCall_t*) pRetSpec->retSpec.head;
		fmock_list_remove(&pRetSpec->retSpec, pRetOnCall);
		free(pRetOnCall);
	}
	free(pRetSpec->fname);
	fmock_list_remove(&fmock_gFuncReturns, pRetSpec);
	free(pRetSpec);
}

static void fmock_freeReturnSpec(void* data)
{
	fmock_returnSpec_t* pRetSpec = (fmock_returnSpec_t*)data;
	if(!pRetSpec)
		return;
	fmock_list_clear(&pRetSpec->retSpec,free);
	free(pRetSpec->fname);
}
void fmock_clearReturnSpecs()
{
	fmock_list_clear(&fmock_gFuncReturns,fmock_freeReturnSpec);
}

/*
 * set expected return on the last expected call
 */
int fmock_returnOnExpectedCall(char* fname, fmock_data_t retValue)
{
	fmock_returnSpec_t* pRetSpec = fmock_searchReturnSpecsByFunc(fname);
	fmock_expect_t* pExpect = fmock_searchExpectByFunc(fname);
	if (!pRetSpec || !pExpect)
		return FMOCK_ERROR;
	if (!pExpect->expectedCalls.tail)
		return FMOCK_ERROR;
	fmock_returnOnCall_t* pRetOnCall = (fmock_returnOnCall_t*) malloc(
			sizeof(fmock_returnOnCall_t));
	memset(pRetOnCall, 0, sizeof(fmock_returnOnCall_t));
	pRetOnCall->call = (fmock_expectCall_t*) pExpect->expectedCalls.tail;
	pRetOnCall->retValue = retValue;
	fmock_list_push(&pRetSpec->retSpec, pRetOnCall);
	return FMOCK_OK;
}
/*
 * set default return value on call
 */
int fmock_defaultReturnOnCall(char* fname, fmock_data_t retValue)
{
	fmock_returnSpec_t* pRetSpec = fmock_searchReturnSpecsByFunc(fname);
	if (!pRetSpec)
		return FMOCK_ERROR;
	fmock_returnOnCall_t* pRetOnCall = (fmock_returnOnCall_t*) malloc(
			sizeof(fmock_returnOnCall_t));
	memset(pRetOnCall, 0, sizeof(fmock_returnOnCall_t));
	pRetOnCall->call = FMOCK_NULL;
	pRetOnCall->retValue = retValue;
	fmock_list_push(&pRetSpec->retSpec, pRetOnCall);
	return FMOCK_OK;
}
