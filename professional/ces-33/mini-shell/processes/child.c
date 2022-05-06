#include <stdlib.h> // malloc | realloc | NULL
#include <string.h> // strcpy | strlen | strcmp
#include <fcntl.h> // open

#include <sys/types.h> // pid_t
#include <unistd.h> // fork | execv | dup2

#include "../strings/strings.h" // prepend
#include "../io/output.h" // syscall_error
#include "child.h"

childp new_child() {
	childp p;

	p.num_arg = 0;
	p.argv = (char**)malloc(sizeof(char*));
	p.argv[0] = NULL;
	p.num_env = 0;
	p.envp = (char**)malloc(sizeof(char*));
	p.envp[0] = NULL;
	p.input_file = (char*)malloc(sizeof(char));
	strcpy(p.input_file, "");
	p.output_file = (char*)malloc(sizeof(char));
	strcpy(p.output_file, "");
	p.pipe_in = -1;
	p.pipe_out = -1;

	return p;
}

childp add_argument(childp p, char *arg) {
	p.argv[p.num_arg] = (char*)malloc((strlen(arg)+1)*sizeof(char));
	strcpy(p.argv[p.num_arg], arg);
	p.num_arg++;
	p.argv = (char**)realloc(p.argv, (p.num_arg + 1)*sizeof(char));
	p.argv[p.num_arg] = NULL;
	return p;
}

void set_input_file(childp p, char *in) {
	strcpy(p.input_file, in);
}

void set_output_file(childp p, char *out) {
	strcpy(p.output_file, out);
}

pid_t childp_create(childp p) {
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

void free_child(childp p) {
	for (int i = 0; p.argv[i] != NULL; i++) {
		free(p.argv[i]);
	}
	free(p.argv);
	for (int i = 0; p.envp[i] != NULL; i++) {
		free(p.envp[i]);
	}
	free(p.envp);
	free(p.input_file);
	free(p.output_file);
}

