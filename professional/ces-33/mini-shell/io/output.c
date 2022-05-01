#include <stdio.h> // printf
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

void echo(char c) {
	putchar(c);
}

void syscall_error(char *program) {
	fprintf(stderr, "%s failed. errno: %d", program, errno);
}

