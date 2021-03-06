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
 * Defines the call expects.
 *---------------------------------------------------------------------------
 *| VERSION | AUTHOR        | DATE       | NOTE                             |
 *---------------------------------------------------------------------------
 *| 01      | Fan Chunquan  | 2017-05-07 | Creation                         |
 *---------------------------------------------------------------------------
 *| 02      | Fan Chunquan  | 2017-12-09 | Support generic type parameters  |
 *---------------------------------------------------------------------------
 */

#ifndef FMOCK_FMOCKEXPECT_H_
#define FMOCK_FMOCKEXPECT_H_

#include <fmock/fmockcommon.h>

#define FMOCK_CHECK_MATCH 0
#define FMOCK_CHECK_UNMATCH 1
typedef int (*fmock_check_proto_t)(void * data, void * refValue);
typedef void (*fmock_data_free_proto_t)(void* data);

typedef struct fmock_data_checker_struct
{
	fmock_data_t compValue;
	fmock_check_proto_t checkFunc; /* checking function */
} fmock_data_checker_t;

extern fmock_data_checker_t fmock_Any();
#define FMOCK_ANY fmock_Any()

extern fmock_data_checker_t fmock_generic_checker(void* refValue, fmock_check_proto_t checkFunc);
#define FMOCK_PARAM_EXPECT(refValue, checkFunc) fmock_generic_checker(refValue, checkFunc)

#include <fmock/fmockbuiltinchecker.h>

extern int fmock_expectCall(char* fname, fmock_data_checker_t checkers[]);

#endif /* FMOCK_FMOCKEXPECT_H_ */
