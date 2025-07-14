#include "shell.h"

void process_input(char **argv, int num_tokens) {
	if (!strcmp(argv[0], "cd")) {
		my_cd(argv);
		return;
	} 
	if (!strcmp(argv[0], "exit")) {
		my_exit(argv);
	}

	if (add_job(argv, num_tokens) != 0) {
		printf("error adding job");
		return;
	}

	if (!strcmp(argv[num_tokens-1], "&")) {
		printf("eureka! bg job!");	
		if (bg_job_handler() == -1){
			return; // already printed error
		}
	}

	// time to handle jobs

	int rc = fork();
	int status;

	// process group for child
	pid_t pg = foreground_pgid; // default to fg
	if (last->is_bg || !foreground_pgid) {
		pg = 0; // make a new pg if needed
	}

	if (rc < 0) {
		printf("Error while forking");
	} else if (rc == 0) {
		sa.sa_handler = SIG_DFL; // listen to ctrlz and ctrlc in child
		if (sigaction(SIGINT, &sa, NULL) || sigaction(SIGTSTP, &sa, NULL)) {
			perror("error ignoring signals");
			exit(1);
		}

		if(setpgid(0, pg)) {
			perror("error setting child pg");
			exit(2);
		}	

		if (execvp(argv[0], argv) == -1)  {
			perror("execvp has failed");
			exit(1);
		}
	} else {
		int setpigiderr = setpgid(rc, pg); // ignore expected errors
		if(setpigiderr && setpigiderr != EINVAL && setpigiderr != EPERM) {
			perror("error setting child pg");
			exit(2);
		}	

		last->pgid = getpgid(rc); // save child pgid 
		printf("process %d, shell: %d\n", last->pgid, getpgid(getpid()));
		last->status = RUNNING;
		if (!last->is_bg) { // wait for foreground tasks
			if (!foreground_pgid) {
				foreground_pgid = last->pgid;
			}
			if (tcsetpgrp(myshell_fd, last->pgid)) { // transfer terminal foreground to child
				perror("error setting child to terminal fg pg");
			}
			waitpid(rc, &status, 0);
			//last->status = DONE; // maybe?
			printf("peakaboo");
			fflush(stdout);
		} else {
			printf("[%d] %d\n", last->jobid, rc);
		}

	}
}
