#include "chain.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * main
 *
 */
int main(int argc, char *argv[])
{
	char line1[256];
	char *input = "input.dat";
	char *output = "output.dat";
	int length;
	int opt;

        while((opt = getopt(argc, argv, ":if:hio")) != -1)
	{
		switch(opt)
		{
		case 'h':
			printf("chain [-h] [-i inputfilename] [-o outputfilename]\n");
			break;
		case 'i':
			input = optarg;
			break;
		case 'o':
			output = optarg;
			break;
		default:
			printf("chain [-h] [-i inputfilename] [-o outputfilename]\n");
			break;
		}
	}

        // Create file descriptor
	int fd = open(input, O_RDONLY);
	int fd2 = open(output, O_WRONLY);

	// Chck for errors
	if (fd == -1 || fd2 == -1)
		perror("Error:");

	// Number of child processes
	readline(fd, line1);
	int children = atoi(line1);
	int pids[children];

        // create the children processes
	for (int i = 0; i < children; i++) {
		pid_t pid = fork();
		if (pid == 0) {
			// child process
			// ... do some stuff ...
			readline(fd, line1);
			length = atoi(line1);
			readline(fd, line1);
			split(fd2, length, line1);
			pids[i] = getpid();
			exit(0);
		}
	}

	// wait for the four children processes to finish
	for (int i = 0; i < children; i++) {
		pid_t pid = wait(NULL);
	}

	char contents[256] = "All children were: ";
	char convert[20];

	for (int j = children - 1; j > 0 ; j--)
	{
		sprintf(convert, "%d", pids[j]);
		int k = strlen(convert);
		if (j != 0)
			convert[k] = ' ';
		strcat(contents, convert);

	}
	write(fd2, contents, strlen(contents));

	close(fd);
	close(fd2);
	return 0;
}
