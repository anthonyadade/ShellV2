#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser/parser.h"
#include "shell/shell.h"
#include "builtins/builtins.h"

int main() {
	char *line = NULL;
        size_t len = 0;
	char **argv;
        ssize_t nread;

	while(1) {
		printf("my_shell$ ");
		nread = getline(&line, &len, stdin); // get input

		if (nread == -1) {
			perror("Error getting input");
		}

		argv = parser(nread, line); 
		process_input(argv);

	}

	free(line);
	return 0;
}
