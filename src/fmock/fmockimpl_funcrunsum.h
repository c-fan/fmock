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

#ifndef FMOCK_FMOCKIMPL_FUNCRUNSUM_H_
#define FMOCK_FMOCKIMPL_FUNCRUNSUM_H_

/*
 * a fmock_funcRunSum_t data structure summarizes run (calls execution) on a specific function mock during a test.
 */
typedef struct
{
	fmock_list_node_t listNode;
	int times; /* how many times called with such expected parameters */
	fmock_expectCall_t* expect;
} fmock_mockCalled_t;
typedef fmock_list_t fmock_called_statistics_t;
typedef struct
{
	fmock_list_node_t listNode;
	char* fname;
	int result; /* pass or fail */
	fmock_called_statistics_t statistics;
	int unexpected; /* number of unexpected calls */
} fmock_funcRunSum_t;
typedef fmock_list_t fmock_funcRunSum_list_t;

extern void fmock_initRunSumByFunc(char* fname);
extern fmock_funcRunSum_t* fmock_searchRunSumByFunc(char* fname);
extern void fmock_clearRunSumByFunc(char* fname);
extern void fmock_clearRunSums();

#endif /* FMOCK_FMOCKIMPL_FUNCRUNSUM_H_ */
