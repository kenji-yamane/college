#include <sys/wait.h>

#include <stdlib.h> // malloc | realloc | NULL
#include <string.h> // strcpy | strlen

#include "../io/output.h"

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
	p.stopped = false;
	p.completed = false;

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

childp set_status(childp p, int status) {
	p.status = status;
	if (WIFSTOPPED(status)) {
		p.stopped = true;
	} else {
		p.completed = true;
		if (WIFSIGNALED(status)) {
			process_terminated(p.pid, WTERMSIG(status));
		}
	}
	return p;
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

