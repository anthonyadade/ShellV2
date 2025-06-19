#include "builtins.h"

int my_exit(char **argv) {
	int status = 0;
	if (argv[1]) {
		status = atoi(argv[1]);
	}
	exit(status);
	return -1; // unreachable code?
}
