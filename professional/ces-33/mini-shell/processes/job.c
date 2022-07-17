#include <stdlib.h> // malloc | free
#include <string.h> // strcpy | strlen | strcmp

#include <sys/types.h> // pid_t
#include <sys/wait.h> // wait
#include <unistd.h>
#include <signal.h>

#include "../strings/strings.h" // prepend
#include "../io/output.h" // syscall_error
#include "job.h"

job create_job(int num_processes, childp *children, char *command) {
	job j;
	j.num_processes = num_processes;
	j.children = children;
	j.command = command;
	j.pipes = (pair*)malloc(num_processes*sizeof(pair));
	j.pgid = 0;
	j.notified = false;
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

job execute_children(shell s, job j, bool foreground) {
	for (int i = 0; i < j.num_processes; i++) {
		pid_t pid = instantiate(j.children[i], j.pgid, foreground);
		if (i == 0) {
			j.pgid = pid;
		}
		setpgid(pid, j.pgid);
		j.children[i].pid = pid;
		if (i < j.num_processes - 1) {
			close(j.pipes[i + 1][1]);
		}
	}
	if (foreground) {
		j = put_in_foreground(s, j, false);
	} else {
		put_in_background(j, false);
	}
	return j;
}

void print_job_info(job j, char *status_name) {
	job_info(j.id, j.pgid, status_name, j.command);
}

void notify_completed_job(job j) {
	print_job_info(j, "completed");
}

job notify_stopped_job(job j) {
	if (j.notified) {
		return j;
	}
	print_job_info(j, "stopped");
	j.notified = true;
	return j;
}

bool job_stopped(job j) {
	for (int i = 0; i < j.num_processes; i++) {
		if (!(j.children[i].stopped || j.children[i].completed)) {
			return false;
		}
	}
	return true;
}

bool job_completed(job j) {
	for (int i = 0; i < j.num_processes; i++) {
		if (!j.children[i].completed) {
			return false;
		}
	}
	return true;
}

void free_job(job j) {
	free(j.pipes);
	free(j.command);
	for (int i = 0; i < j.num_processes; i++) {
		free_child(j.children[i]);
	}
	free(j.children);
}

