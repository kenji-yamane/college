#include <stdlib.h> // malloc | exit | free
#include <string.h> // strcpy | strlen | strcmp
#include <fcntl.h> // open

#include <sys/types.h> // pid_t
#include <sys/wait.h> // wait
#include <unistd.h> // fork | execv | dup2

#include "../strings/strings.h" // prepend
#include "../io/output.h" // syscall_error
#include "manager.h"

pmanager create_pmanager(int num_processes, childp *children) {
	pmanager m;
	m.num_processes = num_processes;
	m.children = children;
	m.pipes = (pair*)malloc(num_processes*sizeof(pair));
	m.children_status = (int*)malloc(num_processes*sizeof(int));
	m.children_pid = (int*)malloc(num_processes*sizeof(int));
	return m;
}

void connect_children(pmanager m) {
	for (int i = 1; i < m.num_processes; i++) {
		pipe(m.pipes[i]);
		m.children[i - 1].pipe_out = m.pipes[i][1];
		m.children[i].pipe_in = m.pipes[i][0];
	}
}

void execute_children(pmanager m) {
	for (int i = 0; i < m.num_processes; i++) {
		pid_t pid = instantiate(m.children[i]);
		m.children_pid[i] = pid;
		waitpid(pid, m.children_status + i, 0);
		if (i < m.num_processes - 1) {
			close(m.pipes[i + 1][1]);
		}
	}
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

void free_manager(pmanager m) {
	free(m.children_pid);
	free(m.children_status);
	free(m.pipes);
	for (int i = 0; i < m.num_processes; i++) {
		free_child(m.children[i]);
	}
	free(m.children);
}

