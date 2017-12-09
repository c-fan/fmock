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
 *| VERSION | AUTHOR        | DATE       | NOTE                             |
 *---------------------------------------------------------------------------
 *| 01      | Fan Chunquan  | 2017-05-20 | Creation                         |
 *---------------------------------------------------------------------------
 *| 02      | Fan Chunquan  | 2017-12-09 | Support generic type parameters  |
 *---------------------------------------------------------------------------
 */

#include <fmock/fmock.h>
#include "fmockimpl_data.h"
#include "fmockimpl_calllog.h"
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <execinfo.h>

static int fmock_checkCallAgainstExpect(fmock_expectCall_t* pExpCall,
		fmock_calledParams_t* pParams)
{
	int result = FMOCK_CHECK_MATCH;
	fmock_expectParam_t* pExpParam =
			(fmock_expectParam_t*) pExpCall->expectedParams.head;
	for (; pExpParam;)
	{
		fmock_calledParam_t* pParam = (fmock_calledParam_t*) fmock_list_at(
				pParams, pExpParam->index);
		result = pExpParam->checker.checkFunc(&pParam->param,
				&pExpParam->checker.compValue);
		if (result == FMOCK_CHECK_UNMATCH)
			break;
		pExpParam = (fmock_expectParam_t*) pExpParam->listNode.next;
	}
	return result;
}
static fmock_expect_t* fmock_searchMatchedExpect(char* fname,
		fmock_calledParams_t* pParams)
{
	fmock_expect_t* pExpect = fmock_searchExpectByFunc(fname);
	return (fmock_expectCall_t*) fmock_list_search(&pExpect->expectedCalls,
			fmock_checkCallAgainstExpect, pParams);
}

/*
 * call a function mock
 */
fmock_return_t __fmock(char* fname, ...)
{
	va_list val;
	fmock_func_t* pfunc = (fmock_func_t*) fmock_searchFuncByName(fname);
	fmock_param_spec_t* pParamSpecs = &pfunc->spec.paramSpec;
	fmock_call_t* pCall = (fmock_call_t*) malloc(sizeof(fmock_call_t));
	memset(pCall, 0, sizeof(fmock_call_t));
	pCall->time = time(FMOCK_NULL);
	pCall->fname = (char*) malloc(strlen(fname) + 1);
	strcpy(pCall->fname, fname);

	va_start(val, fname);
	int paramIndex = 0;
	for (; paramIndex < pfunc->spec.paramNum; paramIndex++)
	{
		fmock_calledParam_t* pParam = (fmock_calledParam_t*) malloc(
				sizeof(fmock_calledParam_t));
		memset(pParam, 0, sizeof(fmock_calledParam_t));
		fmock_param_type_t* pPType = (fmock_param_type_t*) fmock_list_at(
				pParamSpecs, paramIndex);

		switch (pPType->paramType)
		{
		case FMOCK_TYPE_INT:
			pParam->param.i = (long)va_arg(val,long);
			break;
		case FMOCK_TYPE_UINT:
			pParam->param.u = (unsigned long)va_arg(val,unsigned long);
			break;
		case FMOCK_TYPE_FLOAT:
			pParam->param.f = (double)va_arg(val,double);
			break;
		case FMOCK_TYPE_DOUBLE:
			pParam->param.d = (double)va_arg(val,double);
			break;
		case FMOCK_TYPE_STRING:
			pParam->param.s = (char*)va_arg(val,char*);
			break;
		case FMOCK_TYPE_POINTER:
			pParam->param.p = (void*)va_arg(val,void*);
			break;
		case FMOCK_TYPE_GENERIC:
			pParam->param.gv = pPType->parser(val);
			break;
		default:
			/* unsupported type definition, TODO shall not happen */
			break;
		}
		fmock_list_append(&pCall->params, pParam);
	}
	va_end(val);

	pCall->matchedExpect = fmock_searchMatchedExpect(fname, &pCall->params);

	void *btarray[10];
	size_t size;
	size = backtrace(btarray, 10);
	pCall->callStack = backtrace_symbols(btarray, size);
	pCall->callStackSize = size;

	fmock_list_append(&fmock_gCallLog, pCall);

	fmock_funcRunSum_t* pRunSum = fmock_searchRunSumByFunc(fname);
	pCall->retValue = fmock_getDefaultReturnValue(fname);
	if (pCall->matchedExpect)
	{
		fmock_returnOnCall_t* pRetOnCall = fmock_getReturnSpecOnCall(fname,
				pCall->matchedExpect);
		if (pRetOnCall)
		{
			pCall->retValue = pRetOnCall->retValue;
		}
		fmock_recordCallStatisticByExpect(pRunSum, pCall->matchedExpect);
	}
	else
	{
		fmock_recordUnexpectedCall(pCall);
		pRunSum->unexpected++;
	}
	fmock_return_t ret;
	ret.value = pCall->retValue;
	ret.type = pfunc->spec.returnType;
	return ret;
}

