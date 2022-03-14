#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "ft_printf.h"
#include "capt_stdout.h"

#define FMT ""
#define ARG 1

char	*get_stdout(int (*pf)(const char *, ...))
{
	capture_stdout();
	pf(FMT, ARG);
	return (get_captured());
}

void test(char *lib, char *ft)
{
	if (strcmp(lib, ft))
	{
		puts("KO");
		FILE *f = fopen("result", "w");
		fprintf(f, "lib: %s\n\nft : %s\n", lib, ft);
		fclose(f);
	}
	else
	{
		printf("%s\n\n", ft);
		puts("OK");
	}
}

int main()
{
	char *ft = "";
	char *lib;

	lib = get_stdout(printf);
	// ft = get_stdout(ft_printf);
	test(lib, ft);
	free(ft);
	free(lib);
}
