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
 *---------------------------------------------------------------------------
 *| VERSION	| AUTHOR		| DATE			| NOTE							|
 *---------------------------------------------------------------------------
 *| 01		| Fan Chunquan	| 2017-05-20	| Creation						|
 *---------------------------------------------------------------------------
 */

#include <fmock/fmockexpect.h>
#include <fmock/fmockbuiltinchecker.h>

#include <regex.h>

static void fmock_dataChecker_init(fmock_data_checker_t* pChecker)
{
	if (!pChecker)
		return;
	memset(pChecker, 0, sizeof(fmock_data_checker_t));
}

/*
 * Any value will match
 */
int fmock_check_Any(void* data, void* refValue)
{
	return FMOCK_CHECK_MATCH;
}
fmock_data_checker_t fmock_Any()
{
	fmock_data_checker_t checker;
	fmock_dataChecker_init(&checker);
	checker.checkFunc = fmock_check_Any;
	return checker;
}

/*
 * Integer checkers
 */
/* equal */
int fmock_check_iEQ(void* data, void* refValue)
{
	if (*((long*) data) == *((long*) refValue))
	{
		return FMOCK_CHECK_MATCH;
	}
	return FMOCK_CHECK_UNMATCH;
}
fmock_data_checker_t fmock_iEQ(long refValue)
{
	fmock_data_checker_t checker;
	fmock_dataChecker_init(&checker);
	checker.compValue.i = refValue;
	checker.checkFunc = fmock_check_iEQ;
	return checker;
}
/* greater than */
int fmock_check_iGT(void* data, void* refValue)
{
	if (*((long*) data) > *((long*) refValue))
	{
		return FMOCK_CHECK_MATCH;
	}
	return FMOCK_CHECK_UNMATCH;
}
fmock_data_checker_t fmock_iGT(long refValue)
{
	fmock_data_checker_t checker;
	fmock_dataChecker_init(&checker);
	checker.compValue.i = refValue;
	checker.checkFunc = fmock_check_iGT;
	return checker;
}
/* less than */
int fmock_check_iLT(void* data, void* refValue)
{
	if (*((long*) data) < *((long*) refValue))
	{
		return FMOCK_CHECK_MATCH;
	}
	return FMOCK_CHECK_UNMATCH;
}
fmock_data_checker_t fmock_iLT(long refValue)
{
	fmock_data_checker_t checker;
	fmock_dataChecker_init(&checker);
	checker.compValue.i = refValue;
	checker.checkFunc = fmock_check_iLT;
	return checker;
}

/*
 * Unsigned checkers
 */
/* equal */
int fmock_check_uEQ(void* data, void* refValue)
{
	if (*((unsigned long*) data) == *((unsigned long*) refValue))
	{
		return FMOCK_CHECK_MATCH;
	}
	return FMOCK_CHECK_UNMATCH;
}
fmock_data_checker_t fmock_uEQ(unsigned long refValue)
{
	fmock_data_checker_t checker;
	fmock_dataChecker_init(&checker);
	checker.compValue.u = refValue;
	checker.checkFunc = fmock_check_uEQ;
	return checker;
}
/* greater than */
int fmock_check_uGT(void* data, void* refValue)
{
	if (*((unsigned long*) data) > *((unsigned long*) refValue))
	{
		return FMOCK_CHECK_MATCH;
	}
	return FMOCK_CHECK_UNMATCH;
}
fmock_data_checker_t fmock_uGT(unsigned long refValue)
{
	fmock_data_checker_t checker;
	fmock_dataChecker_init(&checker);
	checker.compValue.u = refValue;
	checker.checkFunc = fmock_check_uGT;
	return checker;
}
/* less than */
int fmock_check_uLT(void* data, void* refValue)
{
	if (*((unsigned long*) data) < *((unsigned long*) refValue))
	{
		return FMOCK_CHECK_MATCH;
	}
	return FMOCK_CHECK_UNMATCH;
}
fmock_data_checker_t fmock_uLT(unsigned long refValue)
{
	fmock_data_checker_t checker;
	fmock_dataChecker_init(&checker);
	checker.compValue.u = refValue;
	checker.checkFunc = fmock_check_uLT;
	return checker;
}

/*
 * String checkers
 */
/* equal string */
int fmock_str_EQ(void* data, void* refValue)
{
	char* thedata = (char*) (*(char**) data);
	char* cmpValue = (char*) (*(char**) refValue);
	return strcmp(thedata, cmpValue);
}
fmock_data_checker_t fmock_sEQ(char* refValue)
{
	fmock_data_checker_t checker;
	fmock_dataChecker_init(&checker);
	checker.compValue.s = refValue;
	checker.checkFunc = fmock_str_EQ;
	return checker;
}
/* match (regular expression) */
int fmock_str_reMatch(void* data, void* refValue)
{
	char* thedata = *(char**) data;
	char* pattern = *(char**) refValue;
	regex_t reg;
	char errbuf[1024];
	int err;
	if (regcomp(&reg, pattern, REG_EXTENDED | REG_NOSUB) < 0)
	{
		regerror(err, &reg, errbuf, sizeof(errbuf));
		printf("error:%s\n", errbuf);
	}
	err = regexec(&reg, thedata, 0, 0, 0);
	if (err == 0)
	{
		return FMOCK_CHECK_MATCH;
	}
	else if (err == REG_NOMATCH)
	{
		return FMOCK_CHECK_UNMATCH;
	}
	else
	{
		regerror(err, &reg, errbuf, sizeof(errbuf));
		printf("error:%s\n", errbuf);
		return FMOCK_ERROR;
	}
}
fmock_data_checker_t fmock_sMatch(char* refValue)
{
	fmock_data_checker_t checker;
	fmock_dataChecker_init(&checker);
	checker.compValue.s = refValue;
	checker.checkFunc = fmock_str_reMatch;
	return checker;
}

/*
 * Float checkers
 */
/* equal */
int fmock_check_fEQ(void* data, void* refValue)
{
	if (*((float*) data) == *((float*) refValue))
	{
		return FMOCK_CHECK_MATCH;
	}
	return FMOCK_CHECK_UNMATCH;
}
fmock_data_checker_t fmock_fEQ(float refValue)
{
	fmock_data_checker_t checker;
	fmock_dataChecker_init(&checker);
	checker.compValue.f = refValue;
	checker.checkFunc = fmock_check_fEQ;
	return checker;
}
/* greater than */
int fmock_check_fGT(void* data, void* refValue)
{
	if (*((float*) data) > *((float*) refValue))
	{
		return FMOCK_CHECK_MATCH;
	}
	return FMOCK_CHECK_UNMATCH;
}
fmock_data_checker_t fmock_fGT(float refValue)
{
	fmock_data_checker_t checker;
	fmock_dataChecker_init(&checker);
	checker.compValue.f = refValue;
	checker.checkFunc = fmock_check_fGT;
	return checker;
}
/* less than */
int fmock_check_fLT(void* data, void* refValue)
{
	if (*((float*) data) < *((float*) refValue))
	{
		return FMOCK_CHECK_MATCH;
	}
	return FMOCK_CHECK_UNMATCH;
}
fmock_data_checker_t fmock_fLT(float refValue)
{
	fmock_data_checker_t checker;
	fmock_dataChecker_init(&checker);
	checker.compValue.f = refValue;
	checker.checkFunc = fmock_check_fLT;
	return checker;
}

/*
 * Double float checkers
 */
/* equal */
int fmock_check_dEQ(void* data, void* refValue)
{
	if (*((double*) data) == *((double*) refValue))
	{
		return FMOCK_CHECK_MATCH;
	}
	return FMOCK_CHECK_UNMATCH;
}
fmock_data_checker_t fmock_dEQ(double refValue)
{
	fmock_data_checker_t checker;
	fmock_dataChecker_init(&checker);
	checker.compValue.d = refValue;
	checker.checkFunc = fmock_check_dEQ;
	return checker;
}
/* greater than */
int fmock_check_dGT(void* data, void* refValue)
{
	if (*((double*) data) > *((double*) refValue))
	{
		return FMOCK_CHECK_MATCH;
	}
	return FMOCK_CHECK_UNMATCH;
}
fmock_data_checker_t fmock_dGT(double refValue)
{
	fmock_data_checker_t checker;
	fmock_dataChecker_init(&checker);
	checker.compValue.d = refValue;
	checker.checkFunc = fmock_check_fGT;
	return checker;
}
/* less than */
int fmock_check_dLT(void* data, void* refValue)
{
	if (*((double*) data) < *((double*) refValue))
	{
		return FMOCK_CHECK_MATCH;
	}
	return FMOCK_CHECK_UNMATCH;
}
fmock_data_checker_t fmock_dLT(double refValue)
{
	fmock_data_checker_t checker;
	fmock_dataChecker_init(&checker);
	checker.compValue.d = refValue;
	checker.checkFunc = fmock_check_dLT;
	return checker;
}
