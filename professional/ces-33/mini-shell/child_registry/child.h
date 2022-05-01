#ifndef CHILD_H
#define CHILD_H

#include <sys/types.h> // pid_t

// represents a single child process
typedef struct {
	pid_t pid;
} childp;

/*
 * creates a new process by forking and executing
 *
 * at first it attempts to execute a program locally
 * if it is not found locally, it tries on the /bin folder
 * if none is found, it terminates itself
 */
childp childp_create(char *program);

#endif // child

