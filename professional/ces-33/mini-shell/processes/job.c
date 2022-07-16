#include <stdlib.h> // malloc | exit | free
#include <string.h> // strcpy | strlen | strcmp
#include <fcntl.h> // open

#include <sys/types.h> // pid_t
#include <sys/wait.h> // wait
#include <unistd.h> // fork | execv | dup2
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

void put_in_foreground(job j, bool cont) {
	tcsetpgrp(STDIN_FILENO, j.pgid);

	if (cont) {
		tcsetattr(STDIN_FILENO, TCSADRAIN, &j.tmodes);
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

pid_t instantiate(childp p) {
	pid_t id = fork();
	if (id == -1) {
		syscall_error("fork");
		exit(EXIT_FAILURE);
	}
	if (id != 0) { // success on parent
		return id;
	}

	if (p.pipe_out != -1) {
		dup2(p.pipe_out, STDOUT_FILENO);
	}
	if (p.pipe_in != -1) {
		dup2(p.pipe_in, STDIN_FILENO);
	}
  	if (strcmp(p.input_file, "") != 0) {
		int fd = open(p.input_file, O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
	if (strcmp(p.output_file, "") != 0) {
		int fd = open(p.output_file, O_CREAT | O_WRONLY, 0777);
		dup2(fd, STDOUT_FILENO);
	}
	char *program = p.argv[0];
	execve(program, p.argv, p.envp);

	// past execv means program doesn't exist
	// so, now we try with prefix /bin/
	char *bin_program = prepend("/bin/", p.argv[0]);
	p.argv[0] = bin_program;
	execve(bin_program, p.argv, p.envp);

	syscall_error(program);
	exit(EXIT_FAILURE);
}

void free_job(job j) {
	free(j.pipes);
	for (int i = 0; i < j.num_processes; i++) {
		free_child(j.children[i]);
	}
	free(j.children);
}

