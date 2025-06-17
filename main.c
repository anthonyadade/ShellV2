#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	char *line = NULL;
        size_t len = 0;
        ssize_t nread;
	while(1) {
		printf("my_shell$ ");
		nread = getline(&line, &len, stdin);
		if (!strcmp("exit\n", line) || nread == -1) {
			break;
		}
		printf("here's what you typed: %stype exit to exit\n", line);	
	}
	free(line);
	return 0;
}
