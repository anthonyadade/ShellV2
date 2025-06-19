#include "parser.h"
#include <stdio.h>
char **parser(ssize_t size, char *input) {
	int index = 0; // which token we are on
	
	for (ssize_t i = 0; i < size; i++) {
		if (input[i] == ' ' || i == size - 1) { // if we have reached a space or the newline char
			input[i] = '\0'; // replace it with terminating null char
			index++;
		}
	}

	char **argv = malloc((index + 1) * sizeof(char*)); // add one for null-terminating pointer

	int bp = 0; // beginning pointer, beginning of the current word
	int i = 0;
	for (; i < index; i++) {
		argv[i] = &input[bp]; // we point to the original input that we split up with NULL chars
		bp += strlen(argv[i]) + 1; // move to the start of the next word
	}
	argv[i] = NULL; // null terminate
	return argv;
}
