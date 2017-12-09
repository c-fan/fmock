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
 * An example test using fmock lib
 *---------------------------------------------------------------------------
 *| VERSION | AUTHOR        | DATE       | NOTE                             |
 *---------------------------------------------------------------------------
 *| 01      | Fan Chunquan  | 2017-12-09 | test mock with generic type      |
 *---------------------------------------------------------------------------
 */

#include "user.h"
#include "todo.h"

#include <fmock/fmock.h>

#include <stdio.h>

int todo_t_eq_check(void * data, void * refValue) {
	todo_t* arg = (todo_t*)((fmock_data_t*)data)->gv;
	todo_t* ref = (todo_t*) ((fmock_data_t *)refValue)->gv;
	if ( (arg->v1 == ref->v1) && ( arg->v2 == ref->v2 ) )
		return FMOCK_CHECK_MATCH;
	else
		return FMOCK_CHECK_UNMATCH;
}

FMOCK_DECLARE_MOCK(todo, int, PROTO(todo_t arg), arg);
FMOCK_DECLARE_GENERIC_PARAM_TYPE(todo_t,todo_p0);
void test()
{
	FMOCK_START_TEST(mytest);
	FMOCK_USE_MOCK(todo, "%v", 'i');
	FMOCK_USE_GENERIC_PARAM_TYPE(todo,0,todo_p0);

	todo_t todoarg = {.v1 = 1, .v2 = 2};
	FMOCK_EXPECT_CALL(todo,{FMOCK_PARAM_EXPECT(&todoarg, todo_t_eq_check)});
	FMOCK_LET_RETURN(todo, fmock_intData(1));
	FMOCK_LET_RETURN_BY_DEFAULT(todo,fmock_intData(-1));

	myfunc(1);

	fmock_result_t* mockResult = FMOCK_VERIFY(mytest);
	FMOCK_BRIEF_RESULT(mockResult);
	FMOCK_CLEAR_TEST(mytest);
}

int main(int argc, char** argv)
{
	FMOCK_INIT
	test();
	FMOCK_CLEAR
}
