#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "ft_printf.h"
#include "capt_stdout.h"

#define FMT ""
#define ARG 1

static int get_stdout(char **s, int (*pf)(const char *, ...))
{
	int ret;

	capture_stdout();
	ret = pf(FMT, ARG);
	*s = get_captured();
	return (ret);
}

void test(char *lib, char *ft, int ft_ret, int lib_ret)
{
	if (strcmp(lib, ft) && ft_ret != lib_ret)
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
	// char	*ft;
	// int		ft_ret;
	char	*lib;
	int		lib_ret;

	lib_ret = get_stdout(&lib, printf);
	// ft_ret = get_stdout(&ft, ft_printf);
	// test(lib, ft, ft_ret, lib_ret);
	// free(ft);
	free(lib);
}
