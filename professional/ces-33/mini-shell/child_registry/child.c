#include <stdlib.h> // malloc
#include "../strings/strings.h" // prepend

#include <sys/types.h> // pid_t
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
		return (childp){id};
	}

	char *argv[] = {program, NULL};
	char *envp[] = {NULL};
	execve(program, argv, envp);

	// past execv means program doesn't exist
	// so, now we try with prefix /bin/
	char *bin_program = prepend("/bin/", program);
	argv[0] = bin_program;
	execve(bin_program, argv, envp);
	syscall_error(program);
	exit(EXIT_FAILURE);
}

