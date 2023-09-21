#include <stdio.h>
#include <string.h>
#include <err.h>

#include "error_codes.h"
#include "lexexpr.h"
#include "stdlib.h"

int is_cnum(char c) {return c >= '0' && c <= '9';}
int is_cope(char c) {return c == '+' || c == '*';}

TokDArr new_tokarr()
{
	return (TokDArr){.len=0, .d=malloc(0)};
}

Token new_token()
{
	return (Token){.kind=Tk_EMPTY,.txt=malloc(0),.txt_len=0};
}

void tok_add(TokDArr* arr, Token t)
{
	arr->d = (Token*)realloc(arr->d, (arr->len+1)*sizeof(Token));
	arr->d[arr->len] = t;
	arr->len+=1;
}

void add_char(Token* tok, char c)
{
	tok->txt = (char*)realloc(tok->txt, tok->txt_len+1);
	tok->txt[tok->txt_len] = c;
	tok->txt_len+=1;
}

void term_str(Token* tok)
{
	tok->txt = (char*)realloc(tok->txt, tok->txt_len+1);
	tok->txt[tok->txt_len] = '\0';
}

Tkind find_tk(char c)
{
	switch(c)
	{
		case '*':
			return Tk_STAR;
		case '+':
			return Tk_PLUS;
		default:
			errx(ERR_INVCHAR, ERR_INVCHAR_MSG);
	}
}

TokDArr lex_str(const char* txt)
{
	TokDArr toks = new_tokarr();
	
	for(size_t i=0; txt[i]!='\0'; ++i)
	{
		Token tok = new_token();

		if(is_cnum(txt[i]))
		{
			add_char(&tok, txt[i]);
			++i;
	
			if(txt[i]!='\0' && txt[i-1]=='0' && is_cnum(txt[i]))
				errx(ERR_INVNUMREP, ERR_INVNUMREP_MSG);

			while(txt[i]!='\0' && is_cnum(txt[i]))
			{
				add_char(&tok, txt[i]);
				++i;
			}
			--i;

			term_str(&tok);
			tok.kind = Tk_NUM;
			tok_add(&toks, tok);
		}
		else if(is_cope(txt[i]))
		{
			add_char(&tok, txt[i]);
			term_str(&tok);
			tok.kind = find_tk(txt[i]);
			tok_add(&toks, tok);
		}
		else
		{
			printf("%s\n", txt);

			for(size_t _i=0; _i<i; ++_i)
				printf(" ");
			printf("?\n\n");

			errx(ERR_INVCHAR, ERR_INVCHAR_MSG);
		}
	}

	return toks;
}
