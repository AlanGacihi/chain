#include "chain.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void split(int fd, int length, char *str)
{
	char *token;
	int i = 0;
	int arr[length];
	char contents[256];
	char *convert;
	const char s[2] = " ";

	/*get the first token */
	token = strtok(str, s);

	/* walk through other tokens */
	while(token != NULL)
	{
		if (i < length)
			arr[i++] = atoi(token);
		token = strtok(NULL, s);
	}

	// Check length of integers
	if (length != i)
	{
		fprintf(stderr, "Invalid number of integers\n");
		exit(EXIT_FAILURE);
	}

	// Write to file
	sprintf(contents, "%d", getpid());
	int l = strlen(contents);
	contents[l++] = ':';
	contents[l++] = ' ';
	contents[l] = '\0';

	for (int j = length - 1; j >= 0 ; j--)
	{
		convert = malloc(sizeof(char *) * 20);
		sprintf(convert, "%d", arr[j]);
		int k = strlen(convert);
		if (j != 0)
			convert[k] = ' ';
		else
			convert[k] = '\n';
		strcat(contents, convert);
		free(convert);
	}
	write(fd, contents, strlen(contents));
}
