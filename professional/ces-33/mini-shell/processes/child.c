#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#include <stdlib.h> // malloc | realloc | NULL
#include <string.h> // strcpy | strlen
#include <fcntl.h>

#include "../io/output.h"
#include "../strings/strings.h"

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

void define_ends(childp p) {
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
}

void position_itself(childp p, pid_t pgid, bool foreground) {
	if (pgid == 0) {
		pgid = p.pid;
	}
	setpgid(p.pid, pgid);
	if (foreground) {
		tcsetpgrp(STDIN_FILENO, pgid);
	}

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}

pid_t instantiate(childp p, pid_t pgid, bool foreground) {
    pid_t id = fork();
    if (id == -1) {
        syscall_error("fork");
        exit(EXIT_FAILURE);
    }
    if (id != 0) { // success on parent
        return id;
    }

	p.pid = id;
	position_itself(p, pgid, foreground);
	define_ends(p);

    char *program = p.argv[0];
    execve(program, p.argv, p.envp);

    // past execv means program doesn't exist
    // so, now we try with prefix /bin/
    char *bin_program = prepend("/bin/", p.argv[0]);
    p.argv[0] = bin_program;
    execve(bin_program, p.argv, p.envp);

	// if /bin/ did not work
	// we try now with prefix /usr/bin/
	char *usr_bin_program = prepend("/usr/bin/", p.argv[0]);
	p.argv[0] = usr_bin_program;
	execve(usr_bin_program, p.argv, p.envp);

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

