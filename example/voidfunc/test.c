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
 * An example void function mock test using fmock lib
 *---------------------------------------------------------------------------
 *| VERSION | AUTHOR        | DATE       | NOTE                             |
 *---------------------------------------------------------------------------
 *| 01      | Fan Chunquan  | 2017-07-16 | void function mock test          |
 *---------------------------------------------------------------------------
 */

#include "user.h"
#include "todo.h"

#include <fmock/fmock.h>

#include <stdio.h>

FMOCK_DECLARE_MOCK_V(todo, void, PROTO(int arg1, int arg2), arg1, arg2);
void test()
{
	FMOCK_START_TEST(mytest);
	FMOCK_USE_MOCK(todo, "%i %i", '\0');
	FMOCK_EXPECT_CALL(todo, {fmock_iEQ(102), fmock_iEQ(1)});
	FMOCK_EXPECT_CALL(todo, {fmock_iEQ(104), fmock_iEQ(1)});

	myfunc(1);
	myfunc(2);

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
