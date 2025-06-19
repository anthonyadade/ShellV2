#include "shell.h"

void process_input(char **argv) {
	if (!strcmp(argv[0], "cd")) {
		my_cd(argv);
		return;
	} 
	if (!strcmp(argv[0], "exit")) {
		my_exit(argv);
	}
	int rc = fork();
	if (rc < 0) {
		printf("Error while forking");
	} else if (rc == 0) {
		if (execvp(argv[0], argv) == -1)  {
			perror("execvp has failed");
			exit(1);
		}
	} else {
		int status;
		waitpid(rc, &status, 0);
	}
}
