#pragma once

#include <stddef.h>

enum
{
	Tk_EMPTY,
	Tk_NUM,
	Tk_PLUS,
	Tk_STAR,
};

typedef unsigned char Tkind;

typedef struct {
	Tkind kind;
	char* txt;
	size_t txt_len;
} Token;

typedef struct {
	size_t len;
	Token* d;
} TokDArr;

TokDArr new_tokarr(void);
TokDArr lex_str(const char* txt);
