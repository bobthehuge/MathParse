#ifndef STACK_H
#define STACK_H

#include <stdio.h>

enum {
	ST_TOKEN,
	ST_AST,
};

typedef unsigned char StackType;

struct Stack {
	StackType type;
	void** data;
	size_t len;
	size_t size;
};

typedef struct Stack Stack;

Stack* new_stack(StackType t);
void stack_realloc(Stack* s, size_t nmemb);
void stack_seti(Stack* s, size_t index, void* value);
void stack_geti(Stack* s, size_t index, void* value);
int stack_isempty(Stack* s);
void stack_push(Stack* s, void* value);
void stack_pop(Stack* s, void* value);
void stack_peak(Stack* s, void* value);
void stack_reverse(Stack* s);

#endif
#ifdef STACK_IMPL

#include "parsexpr.h"

Stack* new_stack(StackType t)
{
	Stack* stack_ptr=malloc(sizeof(Stack));
	*(stack_ptr) = (Stack){.type=t, .data=malloc(0), .len=0, .size=0};
	return stack_ptr;
}

void stack_realloc(Stack* s, size_t nmemb)
{
	s->data = realloc(s->data, nmemb*sizeof(void*));
	s->size = nmemb;
}

void stack_seti(Stack* s, size_t index, void* value)
{
	if(index >= s->size)
		return;

	switch(s->type)
	{
		case ST_TOKEN:
			((Token**)s->data)[index] = malloc(sizeof(Token));
			*(((Token**)s->data)[index]) = *((Token*)value);
			break;
		case ST_AST:
			((AST**)s->data)[index] = malloc(sizeof(AST));
			*(((AST**)s->data)[index]) = *((AST*)value);
			break;
		default:
			errx(1, "[ERROR] Unknown StackType\n");
	}
}

void stack_geti(Stack* s, size_t index, void* value)
{
	if(index >= (s->size))
		return;

	switch(s->type)
	{
		case ST_TOKEN:
			*((Token*)value) = *(((Token**)s->data)[index]);
			break;
		case ST_AST:
			*((AST*)value) = *(((AST**)s->data)[index]);
			break;
		default:
			errx(1, "[ERROR] Unknown StackType\n");
	}
}

int stack_isempty(Stack* s)
{
	return s->len == 0;
}

void stack_push(Stack* s, void* value)
{
	stack_realloc(s, s->len+1);
	stack_seti(s, s->len, value);
	s->len++;
}

void stack_pop(Stack* s, void* value)
{
	s->len--;
	stack_geti(s, s->len, value);
	stack_realloc(s, s->len);
}

void stack_peak(Stack* s, void* value)
{
	stack_geti(s, s->len-1, value);
}

void stack_reverse(Stack* s)
{
	for(size_t i=0; i<s->len/2; ++i)
	{
		void* tmp = s->data[i];
		s->data[i] = s->data[s->len-i-1];
		s->data[s->len-i-1] = tmp;
	}
}

#endif
