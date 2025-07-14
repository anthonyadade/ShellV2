#include "jobs.h"

// handles new bg jobs
int bg_job_handler() {
	if (last->argc <2) {
		printf("syntax error near unexpected token `&'");
		remove_job(last->jobid);
		return -1;
	}
	last->argv[last->argc - 1] = NULL; // strip the &
	last->is_bg = true;
	// we have to make sure it leaves the fg group
	return 0;
}

int add_job(char **argv, int num_tokens) {
	struct job *new_job = malloc(sizeof(struct job));

	new_job->childpid = 0;

	// default 	
	new_job->pgid = getpgid(getpid());

	new_job->argv = argv;
	new_job->argc = num_tokens;
	new_job->jobid = last->jobid + 1;
	new_job->status = STOPPED;
	new_job->next = NULL;
	new_job->is_bg = false; // default to false
	last->next = new_job; // old last's next = this
	last = new_job; // update last pointer
	printf("\nadded new job\n");
	return 0;
}

void remove_job() {
	// to be implemented
	//
	pid_t pid;
	int wstatus = 0; // default to successful exit
	if (last->status != DONE) { // if haven't been waited for, WAIT!
		printf("remove_job is handling\n");
		fflush(stdout);
		pid = waitpid(-1, &wstatus, WNOHANG | WUNTRACED | WCONTINUED);
		if (pid == -1 && errno != ECHILD) {
			perror("waitpid 2");
			exit(EXIT_FAILURE);
		}
	}
	printf("remove_Job called");
	fflush(stdout);

	int shellpgid = getpgid(getpid());
	if (WIFEXITED(wstatus) || WIFSIGNALED(wstatus) || WIFSTOPPED(wstatus)) {

		printf("we tried");
		fflush(stdout);
		// if this is not the controlling terminal...
		if (tcgetpgrp(myshell_fd) != shellpgid){
			printf("we tried %d, %d", shellpgid, tcgetpgrp(myshell_fd));
			fflush(stdout);
			if (tcsetpgrp(myshell_fd, shellpgid)) { // transfer terminal foreground back to shell
				perror("error setting childshellpgidg");
			}
			printf("we tried %d, %d", shellpgid, tcgetpgrp(myshell_fd));
			fflush(stdout);
		}

		if (WIFSTOPPED(wstatus)) { // if we are only stopping job
			last->status = STOPPED;
			printf("JOB STOPPED!");
		} else { // else get rid of it
			struct job *cur = dummy;
			while (cur->next != last) {
				cur = cur->next;
			}
			free(cur->next); // remove last
			cur->next = NULL; // remove last (we are assuming)
			last = cur;
			printf("Removing job!\n");

			//printf("exited, status=%d\n", WEXITSTATUS(wstatus));
       			//printf("killed by signal %d\n", WTERMSIG(wstatus));
		}
   	} else if (WIFCONTINUED(wstatus)) {
		last->status = RUNNING;
       		printf("continued\n");
   	}
}

// probably not needed
//handle_sig(int sig) {
	
//}

