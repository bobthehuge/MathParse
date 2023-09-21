#include <stdio.h>
#include <string.h>
#include <err.h>
#include <stdlib.h>

#define STACK_IMPL

#include "error_codes.h"
#include "stack.h"

char* shift_argv(int* argc, char*** argv)
{
	*(argc) -= 1;
	char* t = *(argv)[0];
	*(argv) += 1;
	return t;
}

void print_usage()
{
	printf("usage:\n");
	printf("\t-i\t specify input data\n");
	printf("\t-h\t print this message and exit\n");
}

int main(int argc, char** argv)
{
	/* char* prog = shift_argv(&argc, &argv); */

	if(argc == 1)
	{
		print_usage();
		errx(ERR_NOARG, ERR_NOARG_MSG);
	}

	int i=1;

	while(i < argc)
	{
		/* printf("argv[%d] = '%s'\n", i, argv[i]); */

		if(!strcmp("-i", argv[i]))
		{
			if(i+1 >= argc)
			{
				print_usage();
				errx(ERR_NOEARG, ERR_NOEARG_MSG);
			}

			size_t len = strlen(argv[i+1]);
			char* str = (char*)malloc(len);
			strcpy(str, argv[i+1]);

			TokDArr tokarr = lex_str(str);
	
			printf("%zu token detected\n", tokarr.len);

			for(size_t j=0; j<tokarr.len; ++j)
				printf("val: %s\n", tokarr.d[j].txt);

			Stack* tokens = shunting_yard(tokarr);
			Stack* asts = build_ast(tokens);

			i+=2;
		}
		else if(!strcmp("-h", argv[i]))
		{
			print_usage();
			return ERR_OK;
		}
		else
		{
			print_usage();
			errx(ERR_NOVARG, ERR_NOVARG_MSG);
		}
	}

	return 0;
}
