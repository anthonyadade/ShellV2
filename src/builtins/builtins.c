#include "builtins.h"

// not in use :(
int builtins(char **input) {
	if (input[1] && input[2]){
		printf("Too many arguments\n");
		return -1;
	}
	if (chdir(input[1]) == -1) {
		perror("Error changing directory");
		return -1;
	}
	return 0;
}
