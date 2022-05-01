#include <stdlib.h> // malloc
#include <string.h> // strcat | strlen | strcpy

#include <sys/types.h> // pid_t
#include <sys/wait.h> // waitpid
#include <unistd.h> // fork | execv

#include "../io/output.h" // syscall_error
#include "child.h"

childp childp_create(char *program) {
	pid_t id = fork();
	if (id == -1) {
		syscall_error("fork");
		exit(EXIT_FAILURE);
	}
	if (id != 0) { // success on parent
		//waitpid(id, NULL, 0);
		return (childp){pid: id};
	}

	char *argv[] = {program, NULL};
	char *envp[] = {NULL};
	execve(program, argv, envp);

	// past execv means program doesn't exist
	// so, now we try with prefix /bin/
	char bin_folder[] = "/bin/";
	char *bin_program = (char*)malloc(strlen(bin_folder)*sizeof(char));
	strcpy(bin_program, bin_folder);
	bin_program = (char*)realloc(bin_program, (strlen(bin_program)+strlen(program)-1)*sizeof(char));
	strcat(bin_program, program);

	argv[0] = bin_program;
	execve(bin_program, argv, envp);
	syscall_error(program);
	exit(EXIT_FAILURE);
	return (childp){};
}

