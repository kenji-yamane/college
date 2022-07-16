#include <stdlib.h> // malloc | free
#include <string.h> // strcpy | strlen | strcmp

#include <sys/types.h> // pid_t
#include <sys/wait.h> // wait
#include <unistd.h>
#include <signal.h>

#include "../strings/strings.h" // prepend
#include "../io/output.h" // syscall_error
#include "job.h"

job create_job(int num_processes, childp *children) {
	job j;
	j.num_processes = num_processes;
	j.children = children;
	j.pipes = (pair*)malloc(num_processes*sizeof(pair));
	j.pgid = 0;
	return j;
}

job put_in_foreground(shell s, job j, bool cont) {
	tcsetpgrp(STDIN_FILENO, j.pgid);
	if (cont) {
		tcsetattr(STDIN_FILENO, TCSADRAIN, &j.tmodes);
		if (kill(-j.pgid, SIGCONT) < 0) {
			syscall_error("kill");
		}
	}
	wait_job(j);

	tcsetpgrp(STDIN_FILENO, s.pid);
	tcgetattr(STDIN_FILENO, &j.tmodes);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &s.tmodes);

	return j;
}

void put_in_background(job j, bool cont) {
	if (cont) {
		if (kill(-j.pgid, SIGCONT) < 0) {
			syscall_error("kill");
		}
	}
}

void wait_job(job j) {
	int status;
	for (int i = 0; i < j.num_processes; i++) {
		do {
			waitpid(j.children[i].pid, &status, WUNTRACED);
			j.children[i] = set_status(j.children[i], status);
		} while (!j.children[i].stopped && !j.children[i].completed);
	}
}

void connect_children(job j) {
	for (int i = 1; i < j.num_processes; i++) {
		pipe(j.pipes[i]);
		j.children[i - 1].pipe_out = j.pipes[i][1];
		j.children[i].pipe_in = j.pipes[i][0];
	}
}

void execute_children(job j) {
	for (int i = 0; i < j.num_processes; i++) {
		pid_t pid = instantiate(j.children[i]);
		j.children[i].pid = pid;
		if (i < j.num_processes - 1) {
			close(j.pipes[i + 1][1]);
		}
	}
	wait_job(j);
}

void free_job(job j) {
	free(j.pipes);
	for (int i = 0; i < j.num_processes; i++) {
		free_child(j.children[i]);
	}
	free(j.children);
}

