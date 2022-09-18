#include "chain.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void readline(int fd, char *buffer)
{
       	char ch;
	int i = 0;
	while (read(fd, &ch, sizeof(ch)) > 0 && ch != '\n')
	{
		buffer[i++] = ch;
	}
	buffer[i] = '\0';
}
