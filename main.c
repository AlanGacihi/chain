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
	char line[256];
	char error[128];
	char *input = NULL;
	char *output = NULL;
	int iflag = 0;
	int oflag = 0;
	int length;
	int c;

	// Check options
	opterr = 0;
	while ((c = getopt (argc, argv, "hi:o:")) != -1)
		switch (c)
		{
		case 'h':
			fprintf(stderr, "Usage: chain [-h] [-i inputfilename] [-o outputfilename]\n");
			break;
		case 'i':
			input = optarg;
			iflag = 1;
			break;
		case 'o':
			output = optarg;
			oflag = 1;
			break;
		case '?':
			if (optopt == 'i' || optopt == 'o')
				fprintf (stderr, "Usage: chain [-h] [-i inputfilename] [-o outputfilename]\n");
			else if (isprint (optopt))
				fprintf (stderr, "Unknown option `-%c'.\n", optopt);
			else
				fprintf (stderr,
					 "Unknown option character `\\x%x'.\n",
					 optopt);
			return 1;
		default:
			break;
		}

    // Check input file
	if (iflag == 0)
	{
		fprintf(stderr, "Input file required\n");
		exit(EXIT_FAILURE);		
	}

	// Check putput file
	if (oflag == 0)
	{
		strcat(output, ".out");
	}
	
	//Create file descriptor
	int fd = open(input, O_RDONLY);
	int fd2 = open(output, O_WRONLY | O_CREAT);

	// Chck for errors
	if (fd == -1 || fd2 == -1)
	{
		snprintf(error, sizeof(error), "%s: Error: ", argv[0]);
		perror(error);
		exit(EXIT_FAILURE);
	}

	// Number of child processes
	readline(fd, line);
	int children = atoi(line);
	int pids[children];

        // create the children processes
	for (int i = 0; i < children; i++) {
		pid_t pid = fork();
		if (pid == 0) {
			// child process
			readline(fd, line);
			length = atoi(line);
			readline(fd, line);
			split(fd2, length, line);
			exit(0);
		}
	}

	// wait for the four children processes to finish
	for (int i = 0; i < children; i++) {
		pid_t pid = wait(NULL);
		pids[i] = pid;
	}

	char contents[256] = "All children were: ";
	char *convert;

	// Write to file
	for (int j = 0; j < children ; j++)
	{
		convert = malloc(sizeof(char *) * 20);
		sprintf(convert, "%d", pids[j]);
		int k = strlen(convert);
		if (j != children - 1)
			convert[k] = ' ';
		else
			convert[k] = '\n';
		strcat(contents, convert);
		free(convert);

	}
	convert = malloc(sizeof(char *) * 20);
	sprintf(convert, "%d", getpid());
	strcat(contents, "Parent PID: ");
	strcat(contents, convert);
	strcat(contents, "\n");
	int w = write(fd2, contents, strlen(contents));

	if (w == -1)
	{
		snprintf(error, sizeof(error), "%s: Error:", argv[0]);
		perror(error);
		exit(EXIT_FAILURE);
	}

	close(fd);
	close(fd2);
	free(convert);
	return 0;
}
