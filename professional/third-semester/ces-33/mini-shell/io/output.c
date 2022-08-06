#include <stdio.h> // printf
#include <stdlib.h> // error
#include <unistd.h> // getcwd
#include <errno.h> // errno

#include "output.h"

void welcome_message() {
	printf("Welcome to mini-shell!\n\n\n\n");
}


void prompt() {
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("%s", cwd);
	printf("$ ");
}

void syscall_error(char *program) {
	fprintf(stderr, "%s failed. errno: %d\n", program, errno);
}

void developer_error(char *message) {
	fprintf(stderr, "incorrect usage of internal function: %s\n", message);
	exit(-1);
}

void syntax_error(char *message) {
	fprintf(stderr, "syntax error: %s\n", message);
}

void usage_error(char *message) {
	fprintf(stderr, "incorrect usage: %s\n", message);
}

void process_terminated(int pid, int signal) {
	fprintf(stderr, "%d: Terminated by signal %d\n", pid, signal);
}

void job_info(int id, long pgid, char *status_name, char *command) {
	fprintf(stderr, "[%d] pgid:%ld (%s): %s\n", id, pgid, status_name, command);
}

