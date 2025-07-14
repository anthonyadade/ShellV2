#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "parser/parser.h"
#include "shell/shell.h"
#include "builtins/builtins.h"
#include "jobs/jobs.h"

struct job *dummy;
struct job *last;
pid_t foreground_pgid;
int myshell_fd; // this shell's file descriptor
struct sigaction sa;

int main() {

	//initialize global
	dummy = malloc(sizeof(struct job));
	dummy->jobid = 0;
	last = dummy;
	//foreground_pgid = getpgid(getpid());
	myshell_fd = open("/dev/tty", O_RDONLY); // this teminals file descriptor, used in tcsetpgrp

	char *line = NULL;
        size_t len = 0;
	char **argv;
        ssize_t nread;
	int *num_tokens = malloc(sizeof(int));

//	int do_nothing = SIG_IGN; // ignore signal
//	int restore = SIG_DFL; // listen to signals again
	
	sa.sa_handler = SIG_IGN; // ignore signal
	if (sigaction(SIGINT, &sa, NULL) || sigaction(SIGTSTP, &sa, NULL)) {
		perror("error ignoring signals");
		return -1;
	}

	sa.sa_handler = &remove_job; // reap finished jobs
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL)) {
		perror("error setting finished jobs to be reaped");
		return -1;
	}

	while(1) {
		printf("my_shell$ ");
		nread = getline(&line, &len, stdin); // get input

		if (nread == -1) {
			perror("Error getting input");
		}

		argv = parser(nread, line, num_tokens); 
		process_input(argv, *num_tokens);

	}

	free(line);
	free(num_tokens);
	return 0;
}
