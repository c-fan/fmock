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
 * Defines the return data for function mock.
 *---------------------------------------------------------------------------
 *| VERSION	| AUTHOR		| DATE			| NOTE							|
 *---------------------------------------------------------------------------
 *| 01		| Fan Chunquan	| 2017-05-07	| Creation						|
 *---------------------------------------------------------------------------
 */

#ifndef FMOCK_FMOCKRETURN_H_
#define FMOCK_FMOCKRETURN_H_

#include <fmock/fmockcommon.h>

/*
 * specify default return value for a mocked function
 */
extern int fmock_defaultReturnOnCall(char* fname, fmock_data_t retValue);

/*
 * specify return value for the last call expect specified
 */
extern int fmock_returnOnExpectedCall(char* fname, fmock_data_t retValue);

typedef struct
{
	fmock_type_t type;
	fmock_data_t value;
} fmock_return_t;

#endif /* FMOCK_FMOCKRETURN_H_ */
