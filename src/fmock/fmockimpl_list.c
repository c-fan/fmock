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
 *| 01		| Fan Chunquan	| 2017-05-07	| Creation						|
 *---------------------------------------------------------------------------
 */

#include <fmock/fmockcommon.h>

void fmock_list_init(fmock_list_t * l)
{
	memset(l, 0, sizeof(fmock_list_t));
}

void fmock_list_append(fmock_list_t * l, fmock_list_node_t * n)
{
	if (l->tail)
	{
		l->tail->next = n;
	}
	else
	{ // empty list yet
		l->head = n;
	}
	l->tail = n;
	l->size++;
}

void fmock_list_push(fmock_list_t * l, fmock_list_node_t * n)
{
	n->next = l->head;
	if (!l->head)
	{ // empty list yet
		l->tail = n;
	}
	l->head = n;
	l->size++;
}

void fmock_list_remove(fmock_list_t *l, fmock_list_node_t * n)
{
	fmock_list_node_t * it = l->head;
	fmock_list_node_t * prev = FMOCK_NULL;
	while (it)
	{
		if (it == n)
		{
			if (prev)
			{
				prev->next = it->next;
			}
			else
			{ // first node
				l->head = it->next;
			}
			l->size--;
			break;
		}
		else
		{
			prev = it;
			it = it->next;
		}
	}
	if (l->head == FMOCK_NULL)
	{
		l->tail = FMOCK_NULL;
	}
}

void fmock_list_clear(fmock_list_t *l, fmock_list_freeNode_proto_t freeNodeFunc)
{
	fmock_list_node_t * it = l->head;
	if (it)
	{
		l->head = it->next;
		freeNodeFunc(it);
		it = l->head;
	}
	l->tail = FMOCK_NULL;
	l->size = 0;
}

// index start from 0
fmock_list_node_t * fmock_list_at(fmock_list_t *l, int index)
{
	fmock_list_node_t * it = l->head;
	int i = 0;
	for (; i < index; i++)
	{
		if (it)
		{
			it = it->next;
		}
		else
		{
			break;
		}
	}
	if (i == index)
	{
		return it;
	}
	else
	{
		return FMOCK_NULL;
	}
}

fmock_list_node_t * fmock_list_search(fmock_list_t *l,
		fmock_compare_proto_t compFunc, void * data)
{
	fmock_list_node_t * it = l->head;
	while (it)
	{
		if (compFunc(it, data) == 0)
		{
			break;
		}
		else
		{
			it = it->next;
		}
	}
	return it;
}
