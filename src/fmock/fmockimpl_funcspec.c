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

#include "fmockimpl_funcspec.h"
#include "fmockimpl_data.h"

int fmock_initFunctionSpec(char* fname, char* argDefinition, char returnType)
{
	int validDef = 1; /* is definition valid */
	fmock_func_t * pfunc = (fmock_func_t*) malloc(sizeof(fmock_func_t));
	memset(pfunc, 0, sizeof(fmock_func_t));
	pfunc->fname = (char*) malloc(strlen(fname) + 1);
	strcpy(pfunc->fname, fname);
	pfunc->argdefn = (char*) malloc(strlen(argDefinition) + 1);
	strcpy(pfunc->argdefn, argDefinition);
	pfunc->spec.paramNum = 0;
	pfunc->spec.returnType = returnType;
	fmock_param_type_t* ptype;
	int index = 0;
	char* argdefn = argDefinition;
	for (; *argdefn; argdefn++)
	{
		if (*argdefn == '\0')
			break;
		if (*argdefn != '%')
			continue;
		argdefn++;
		ptype = (fmock_param_type_t*) malloc(sizeof(fmock_param_type_t));
		memset(ptype, 0, sizeof(fmock_param_type_t));
		ptype->index = index++;
		switch (*argdefn)
		{
		case 'i':
			ptype->paramType = FMOCK_TYPE_INT;
			break;
		case 'u':
			ptype->paramType = FMOCK_TYPE_UINT;
			break;
		case 'f':
			ptype->paramType = FMOCK_TYPE_FLOAT;
			break;
		case 'd':
			ptype->paramType = FMOCK_TYPE_DOUBLE;
			break;
		case 's':
			ptype->paramType = FMOCK_TYPE_STRING;
			break;
		case 'p':
			ptype->paramType = FMOCK_TYPE_POINTER;
			break;
		default:
			/* unsupported type definition */
			validDef = 0;
			free(ptype);
			index--;
			break;
		}
		if (validDef)
		{
			fmock_list_append(&pfunc->spec.paramSpec, ptype);
		}
		else
		{
			break;
		}
	}
	if (validDef)
	{
		pfunc->spec.paramNum = index;
		fmock_list_append(&fmock_gFunctionMocks, pfunc);
		return FMOCK_OK;
	}
	else
	{
		for (; pfunc->spec.paramSpec.head;)
		{
			fmock_param_type_t* pPType =
					(fmock_param_type_t*) pfunc->spec.paramSpec.head;
			fmock_list_remove(&pfunc->spec.paramSpec, pPType);
			free(pPType);
		}
		fmock_list_remove(&fmock_gFunctionMocks, pfunc);
		free(pfunc->fname);
		free(pfunc->argdefn);
		free(pfunc);
		return FMOCK_ERROR;
	}
}

static int fmock_funcSpec_cmp(void * node, void * compValue)
{
	fmock_func_t* pfunc = (fmock_func_t*) node;
	char* fname = (char*) compValue;
	return strcmp(pfunc->fname, fname);
}

fmock_func_t* fmock_searchFuncByName(char* fname)
{
	return (fmock_func_t*) fmock_list_search(&fmock_gFunctionMocks,
			fmock_funcSpec_cmp, fname);
}

int fmock_clearFunctionSpec(char* fname)
{
	fmock_func_t* pfunc = fmock_searchFuncByName(fname);
	if (!pfunc)
	{
		return FMOCK_ERROR;
	}
	for (; pfunc->spec.paramSpec.head;)
	{
		fmock_param_type_t* pPType =
				(fmock_param_type_t*) pfunc->spec.paramSpec.head;
		fmock_list_remove(&pfunc->spec.paramSpec, pPType);
		free(pPType);
	}
	fmock_list_remove(&fmock_gFunctionMocks, pfunc);
	free(pfunc->fname);
	free(pfunc->argdefn);
	free(pfunc);
	return FMOCK_OK;
}

static void fmock_freeFunctionSpec(fmock_list_node_t * data)
{
	fmock_func_t* pfunc = (fmock_func_t*) data;
	if (pfunc)
	{
		for (; pfunc->spec.paramSpec.head;)
		{
			fmock_param_type_t* pPType =
					(fmock_param_type_t*) pfunc->spec.paramSpec.head;
			fmock_list_remove(&pfunc->spec.paramSpec, pPType);
			free(pPType);
		}
		free(pfunc->fname);
		free(pfunc->argdefn);
		free(pfunc);
	}
}
void fmock_clearAllFunctionSpecs()
{
	fmock_list_clear(&fmock_gFunctionMocks, fmock_freeFunctionSpec);
}

