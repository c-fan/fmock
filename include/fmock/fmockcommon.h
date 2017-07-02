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
 * Common data definition including a simple list implementation.
 * In the fmock lib implementation, list will be heavily used to organize data.
 * This doesn't mean that it's the best data structure, however. Actually,
 * there's quite some situation that maybe better to organize data with other
 * data structure. I use list only to keep the total code small & don't want to
 * have too much overhead. Anyway, it's just a simple mock lib.
 *---------------------------------------------------------------------------
 *| VERSION	| AUTHOR		| DATE			| NOTE							|
 *---------------------------------------------------------------------------
 *| 01		| Fan Chunquan	| 2017-05-07	| Creation						|
 *---------------------------------------------------------------------------
 */

#ifndef FMOCK_FMOCKCOMMON_H_
#define FMOCK_FMOCKCOMMON_H_

#define FMOCK_OK 0
#define FMOCK_KO 1
#define FMOCK_ERROR -1

#define FMOCK_NULL 0

/*
 * data
 */
typedef union
{
	long i;
	unsigned long u;
	float f;
	double d;
	char * s;
	void * p;
} fmock_data_t;

typedef enum
{
	FMOCK_TYPE_INT = 'i',
	FMOCK_TYPE_UINT = 'u',
	FMOCK_TYPE_FLOAT = 'f',
	FMOCK_TYPE_DOUBLE = 'd',
	FMOCK_TYPE_STRING = 's',
	FMOCK_TYPE_POINTER = 'p'
} fmock_type_t;

extern fmock_data_t fmock_intData(long value);
extern fmock_data_t fmock_unsignedData(unsigned long value);
extern fmock_data_t fmock_floatData(float value);
extern fmock_data_t fmock_doubleData(double value);
extern fmock_data_t fmock_stringData(char* value);
extern fmock_data_t fmock_pointerData(void* value);

/*
 * simple list
 */
typedef struct fmock_list_node_struct
{
	struct fmock_list_node_struct * next;
} fmock_list_node_t;

typedef struct
{
	int size; // list size
	fmock_list_node_t * head; // first node
	fmock_list_node_t * tail; // last node, for better performance
} fmock_list_t;

typedef int (*fmock_compare_proto_t)(void * param, void * compValue);
//typedef void (*fmock_list_freeNode_proto_t)(fmock_list_node_t * data);
typedef void (*fmock_list_freeNode_proto_t)(void * data);

extern void fmock_list_init(fmock_list_t * l);

extern void fmock_list_append(fmock_list_t * l, fmock_list_node_t * n);

extern void fmock_list_push(fmock_list_t * l, fmock_list_node_t * n);

extern void fmock_list_remove(fmock_list_t *l, fmock_list_node_t * n);

extern void fmock_list_clear(fmock_list_t *l,
		fmock_list_freeNode_proto_t freeNodeFunc);

extern fmock_list_node_t * fmock_list_at(fmock_list_t *l, int index);

extern fmock_list_node_t * fmock_list_search(fmock_list_t *l,
		fmock_compare_proto_t compFunc, void * data);

#endif /* FMOCK_FMOCKCOMMON_H_ */
