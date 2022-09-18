#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main (int argc, char **argv)
{
	int aflag = 0;
	int bflag = 0;
	char *ivalue = "input.dat";
	char *ovalue = "output.dat";
	int index;
	int c;

	opterr = 0;

	while ((c = getopt (argc, argv, "hi:o:")) != -1)
		switch (c)
		{
		case 'h':
			printf("chain [-h] [-i inputfilename] [-o outputfilename]\n");
			break;
		case 'i':
			ivalue = optarg;
			break;
		case 'o':
			ovalue = optarg;
			break;
		case '?':
			if (optopt == 'i' || optopt == 'o')
				fprintf (stderr, "Option -%c requires an argument.\n", optopt);
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

	printf ("aflag = %d, bflag = %d, ivalue = %s\n, ovalue = %s\n",
		aflag, bflag, ivalue, ovalue);

	for (index = optind; index < argc; index++)
		printf ("Non-option argument %s\n", argv[index]);
	return 0;
}
