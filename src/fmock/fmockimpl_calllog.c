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
 */

#include <fmock/fmockcommon.h>
#include <fmock/fmocktest.h>

#include "fmockimpl_calllog.h"
#include "fmockimpl_data.h"

#include <string.h>
#include <stdlib.h>

void fmock_clearCallLog()
{
	for (; fmock_gCallLog.head;)
	{
		fmock_call_t* pCall = (fmock_call_t*) fmock_gCallLog.head;
		fmock_list_clear(&pCall->params, free);
		free(pCall->fname);
		if (pCall->callStack)
		{
			free(pCall->callStack);
		}
		fmock_list_remove(&fmock_gCallLog, pCall);
		free(pCall);
	}
}

/*
 * Record unexpected calls
 */
static fmock_unexpectedCallRecord_t* fmock_makeUnexpectedCallRecord(
		fmock_call_t* pUnexpectedCall)
{
	if (!pUnexpectedCall)
		return FMOCK_NULL;
	fmock_unexpectedCallRecord_t* pUnexpCallRec =
			(fmock_unexpectedCallRecord_t*) malloc(
					sizeof(fmock_unexpectedCallRecord_t));
	memset(pUnexpCallRec, 0, sizeof(fmock_unexpectedCallRecord_t));
	pUnexpCallRec->fname = (char*) malloc(strlen(pUnexpectedCall->fname) + 1);
	strcpy(pUnexpCallRec->fname, pUnexpectedCall->fname);
	char callinfo[_FMOCK_MAX_RECORD_LENGTH];
	memset(callinfo, '\0', _FMOCK_MAX_RECORD_LENGTH);
	int infoSize = 0;
	sprintf(callinfo, "@ %s\n", ctime(&pUnexpectedCall->time));
	int i = 2;
	for (; i < pUnexpectedCall->callStackSize; i++)
	{
		infoSize = strlen(callinfo);
		sprintf(callinfo + infoSize, "\t%s\n", pUnexpectedCall->callStack[i]);
	}
	infoSize = strlen(callinfo);
	pUnexpCallRec->callinfo = (char*) malloc(infoSize + 1);
	strcpy(pUnexpCallRec->callinfo, callinfo);
	return pUnexpCallRec;
}
void fmock_recordUnexpectedCall(fmock_call_t* pUnexpectedCall)
{
	fmock_unexpectedCallRecord_t* pUnexpCallRec =
			fmock_makeUnexpectedCallRecord(pUnexpectedCall);
	if (pUnexpCallRec)
	{
		fmock_list_append(&fmock_gUnexpectedRecords, pUnexpCallRec);
	}
}

void fmock_clearUnexpectedCallRecords()
{
	fmock_list_node_t* pThisRec;
	fmock_unexpectedCallRecord_t* pUnexpCallRec;
	pThisRec = fmock_gUnexpectedRecords.head;
	for (; pThisRec;)
	{
		fmock_unexpectedCallRecord_t* pUnexpCallRec =
				(fmock_unexpectedCallRecord_t*) pThisRec;
		pThisRec = pThisRec->next;
		free(pUnexpCallRec->callinfo);
		free(pUnexpCallRec->fname);
		fmock_list_remove(&fmock_gUnexpectedRecords, pUnexpCallRec);
		free(pUnexpCallRec);
	}
}
