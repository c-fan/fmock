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
 *| 01      | Fan Chunquan  | 2017-05-28 | Creation                         |
 *---------------------------------------------------------------------------
 *| 02      | Fan Chunquan  | 2017-12-10 | Bug fix                          |
 *---------------------------------------------------------------------------
 */

#include <fmock/fmock.h>
#include "fmockimpl_calllog.h"
#include "fmockimpl_result.h"
#include "fmockimpl_data.h"
#include <stdlib.h>
#include <string.h>

void fmock_initResult(char* tname)
{
	fmock_gResult.result = FMOCK_PASS;
	fmock_gResult.tname = (char*) malloc(strlen(tname) + 1);
	strcpy(fmock_gResult.tname, tname);
	fmock_gResult.unexpected = 0;
}

/* clear test result */
void fmock_clearResult(char* tname)
{
	free(fmock_gResult.tname);
}

/* verify per test */
fmock_result_t* __fmock_verify_result(char* tname)
{
	if (strcmp(fmock_gResult.tname, tname) != 0)
	{
		return FMOCK_NULL; /* wrong test context */
	}
	fmock_funcRunSum_t* pFuncRunSum =
			(fmock_funcRunSum_t*) fmock_gFuncRunSummaries.head;
	while (pFuncRunSum)
	{
		pFuncRunSum->result = FMOCK_PASS;
		if (pFuncRunSum->unexpected != 0)
		{
			pFuncRunSum->result = FMOCK_FAIL;
			fmock_gResult.result = FMOCK_FAIL;
			fmock_gResult.unexpected += pFuncRunSum->unexpected;
		}
		pFuncRunSum = (fmock_funcRunSum_t*) pFuncRunSum->listNode.next;
	}
	fmock_gResult.unexpectedCalls = fmock_gUnexpectedRecords;
	return &fmock_gResult;
}

void __fmock_print_result_summary(fmock_result_t* pResult)
{
	if (pResult == FMOCK_NULL)
	{
		printf("ERROR!\n");
		return;
	}
	printf("FMOCK test %s:", pResult->tname);
	printf("\t%s\n", (pResult->result == FMOCK_PASS) ? "PASS!" : "FAIL!");
}

void __fmock_print_result_detail(fmock_result_t* pResult)
{
	if (pResult == FMOCK_NULL)
	{
		printf("ERROR!\n");
		return;
	}
	printf("FMOCK test result for %s:\n", pResult->tname);
	printf("\t\t%s\n", (pResult->result == FMOCK_PASS) ? "PASS!" : "FAIL!");
	if (pResult->result != FMOCK_PASS)
	{
		printf("\tUnexpected Calls:\t%d\n", pResult->unexpected);
		int i=0;
		for(;i<pResult->unexpected;i++)
		{
			fmock_unexpectedCallRecord_t* pUnexpCallRec = (fmock_unexpectedCallRecord_t*)fmock_list_at(&fmock_gResult.unexpectedCalls,i);
			printf("\t[%d] unexpected call to %s, %s \n", i+1, pUnexpCallRec->fname, pUnexpCallRec->callinfo);
		}
	}
}
