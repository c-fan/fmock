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
 * Defines the data of test result.
 * Users may make use of the result to work with their test framework.
 *---------------------------------------------------------------------------
 *| VERSION | AUTHOR        | DATE       | NOTE                             |
 *---------------------------------------------------------------------------
 *| 01      | Fan Chunquan  | 2017-05-28 | Creation                         |
 *---------------------------------------------------------------------------
 *| 02      | Fan Chunquan  | 2017-07-30 | Simpler test clear interface     |
 *---------------------------------------------------------------------------
 */

#ifndef FMOCK_FMOCKTEST_H_
#define FMOCK_FMOCKTEST_H_

#define FMOCK_PASS 0
#define FMOCK_FAIL 1

#define _FMOCK_MAX_RECORD_LENGTH 1000
typedef struct
{
	fmock_list_node_t listNode;
	char* fname;
	char* callinfo;
} fmock_unexpectedCallRecord_t;
typedef fmock_list_t fmock_unexpectedCallRecord_list_t;

typedef struct
{
	/* fmock_list_node_t listNode;*/
	char* tname;
	int result; /* pass or fail: FMOCK_PASS, FMOCK_FAIL */
	int unexpected; /* number of unexpected calls */
	fmock_unexpectedCallRecord_list_t unexpectedCalls;
} fmock_result_t;
/*typedef fmock_list_t fmock_result_list_t;*/ /* support one test only */

extern int __fmock_start_test(char* tid);

extern fmock_result_t* __fmock_verify_result(char* tname);

extern void __fmock_print_result_summary(fmock_result_t* pResult);

extern void __fmock_print_result_detail(fmock_result_t* pResult);

extern int __fmock_clear_test(char* tname);

#define FMOCK_START_TEST(tname) \
	do { \
		__fmock_start_test(#tname); \
	} while(0)

#define FMOCK_VERIFY(tname) __fmock_verify_result(#tname)

#define FMOCK_BRIEF_RESULT(result) __fmock_print_result_summary(result)

#define FMOCK_DETAIL_RESULT(result) __fmock_print_result_detail(result)

#define FMOCK_CLEAR_TEST(tname) \
	do { \
		__fmock_clear_test(#tname); \
	} while(0)

#endif /* FMOCK_FMOCKTEST_H_ */
