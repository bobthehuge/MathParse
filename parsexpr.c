#include <stdlib.h>
#include <stdio.h>
#include <err.h>

#include "lexexpr.h"
#include "stack.h"
#include "error_codes.h"

int is_toknum(Token tok){return tok.kind==Tk_NUM;}
int is_tokope(Token tok){
	return 
		tok.kind == Tk_PLUS || 
		tok.kind == Tk_STAR;
}

int get_argc(Token tok)
{
	if(tok.txt[0] == '+' ||
		 tok.txt[0] == '*'	 )
	{
		return 2;
	}
	else
		errx(ERR_UNEXPTOK, ERR_UNEXPTOK_MSG);
}

int get_precedence(Token tok)
{
	Tkind t=tok.kind;

	if(t == Tk_PLUS)
		return 2;
	else if (t == Tk_STAR)
		return 1;
	else
		errx(ERR_UNEXPTOK, ERR_UNEXPTOK_MSG);
}

Stack* shunting_yard(TokDArr toks)
{
	Stack* out = new_stack(ST_TOKEN);
	Stack* ope = new_stack(ST_TOKEN);

	Token* tmp = malloc(sizeof(Token));
	tmp->kind = Tk_EMPTY;

	for(size_t i=0; i<toks.len; ++i)
	{
		if(is_toknum(toks.d[i]))
		{
			stack_push(out, &toks.d[i]);
		}
		else if(is_tokope(toks.d[i]))
		{
			stack_peak(ope, tmp);

			while(ope->len > 0 && tmp->kind != Tk_EMPTY &&
					get_precedence(*tmp) <= get_precedence(toks.d[i]))
			{
				stack_pop(ope, tmp);
				stack_push(out, tmp);
			}

			stack_push(ope, &toks.d[i]);
		}
		else
		{
			printf("Token: %s\n", toks.d[i].txt);
			errx(ERR_UNEXPTOK, ERR_UNEXPTOK_MSG);
		}
	}

	while(ope->len > 0)
	{
		stack_pop(ope, tmp);
		stack_push(out, tmp);
	}

	return out;
}

Stack* build_ast(Stack* toks)
{
	Stack* out = new_stack(ST_AST);
	stack_reverse(toks);
	return out;
}
