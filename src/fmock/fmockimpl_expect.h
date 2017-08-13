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

#ifndef FMOCK_FMOCKIMPL_EXPECT_H_
#define FMOCK_FMOCKIMPL_EXPECT_H_

#include <fmock/fmockexpect.h>

typedef struct
{
	fmock_list_node_t listNode;
	int index; /* which parameter */
	fmock_data_checker_t checker;
} fmock_expectParam_t;

typedef fmock_list_t fmock_expectParamList_t;

typedef struct
{
	fmock_list_node_t listNode;
	fmock_expectParamList_t expectedParams;
} fmock_expectCall_t;

typedef fmock_list_t fmock_expectedCallList_t;

typedef struct
{
	fmock_list_node_t listNode;
	char* fname;
	fmock_expectedCallList_t expectedCalls;
} fmock_expect_t;

typedef fmock_list_t fmock_expects_t;

extern fmock_expect_t* fmock_searchExpectByFunc(char* fname);

extern void fmock_initExpectByFunc(char* fname);
extern void fmock_clearExpectByFunc(char* fname);

extern void fmock_clearExpects();

#endif /* FMOCK_FMOCKIMPL_EXPECT_H_ */
