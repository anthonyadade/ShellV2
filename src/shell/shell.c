#include "shell.h"

void process_input(char** argv) {
	int rc = fork();
	if (rc < 0) {
		printf("Error while forking");
	} else if (rc == 0) {
		//for now we will support execvp system calls
		if (execvp(argv[0], argv) == -1)  {
			int err = errno; // prob gonna try to just print this soon
			printf("execvp has failed with errno: %d\n", err);
		}
	} else {
		wait(NULL);
	}
}
