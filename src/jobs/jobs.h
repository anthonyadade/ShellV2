#ifndef JOBS_H
#define JOBS_H

#include <stdbool.h>
#include <sys/types.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

extern struct job *dummy;
extern struct job *last;
extern int myshell_fd; // this shell's file descriptor

enum job_status {
	RUNNING,
	STOPPED,
	DONE // might not need, since DONE jobs are removed from table
};

struct job {
	int childpid;
	pid_t pgid; // process group id
	char **argv; // command string
	int argc;
	int jobid;
	enum job_status status;
	struct job *next;
	bool is_bg; // background task?
};

//int bg_job_handler(char **argv, int num_tokens);
int bg_job_handler();
int add_job(char **argv, int num_tokens);
void remove_job();

#endif // JOBS_H
