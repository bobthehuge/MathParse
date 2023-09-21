#pragma once

#include "lexexpr.h"

typedef struct {
	Token* data;
	size_t len;
} TokStack;

struct AST{
	Token root;
	struct AST* left;
	struct AST* right;
};
typedef struct AST AST;

Stack* build_ast(Stack* tokens);
Stack* shunting_yard(TokDArr tokens);
