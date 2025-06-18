#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser/parser.h"
#include "shell/shell.h"

int main() {
	char *line = NULL;
        size_t len = 0;
	char **argv;
        ssize_t nread;

	while(1) {
		printf("my_shell$ ");
		nread = getline(&line, &len, stdin);

		if (!strcmp("exit\n", line) || nread == -1) {
			break;
		} else {
			argv = parser(nread, line);
			process_input(argv);
		}

		//printf("here's the second word you typed: %stype exit to exit\n", argv[1]);	

	}

	free(line);
	return 0;
}
