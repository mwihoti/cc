#include "main.h"

int main(int ac, char **argv)
{

	char *prompt = "$ ";
	char *lineptr = NULL ;
	size_t n = 0;
	ssize_t nchars_read;

	(void)ac;

	(void)argv;
	while (1)
	{
	printf("%s", prompt);
	nchars_read = getline(&lineptr, &n, stdin);
	if (nchars_read == -1)
	{
		printf("Exited shell\n");
		return (-1);
	}
	printf("%s\n", lineptr);
	free(lineptr);
	lineptr = NULL;
	}
	return (0);
}
