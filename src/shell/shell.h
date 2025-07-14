#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include "../builtins/builtins.h"
#include "../jobs/jobs.h"

extern struct job *dummy;
extern struct job *last;
extern pid_t foreground_pgid;
extern int myshell_fd; // this shell's file descriptor
extern struct sigaction sa;

void process_input(char **argv, int num_tokens);
