#include "parser.h"
#include <stdio.h>
char** parser(ssize_t size, char* input) {
	char **argv = malloc(2 * sizeof(char*));
	//argv = malloc(2 * sizeof(char*)); // initializing output
	char cur[size+1]; // setting to max possible size including null byte
	int index = 0; // which token we are on
	int j = 0;
	for (ssize_t i = 0; i <= size; i++) {
		if (i == size || input[i] == ' ') { // if we have reached the end or a space
			argv[index] = malloc(strlen(cur) + 1); // then append this token to our result
			cur[j] = '\0';
			j = 0;
			strcpy(argv[index], cur);
			index++;
		} else {
			cur[j] = input[i];
			j++;
		}
	}
			return argv;
}
