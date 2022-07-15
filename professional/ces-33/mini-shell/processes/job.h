#ifndef MANAGER_H
#define MANAGER_H

#include <sys/types.h> // pid_t

#include "child.h"

typedef int pair[2];

/*
 * job bundles an array of child
 * structures and instantiates
 * processes from each one of the
 * children. It binds consecutive
 * processes with a pipe
 */
typedef struct {
	int num_processes;
	childp *children;
	pair *pipes;
	int *children_status;
	int *children_pid;
} job;

// instantiates a job structure, allocating space for
// the arrays that will contain metadata relative to
// the created processes
job create_job(int num_processes, childp *children);

// pipes ith child's output to its successor's input
void connect_children(job m);

// instantiates each child sequentially, waiting
// for the end of the ith child to close its
// output and then instantiate the successor
void execute_children(job m);

/*
 * creates a new process by forking and executing
 *
 * at first it attempts to execute a program locally
 * if it is not found locally, it tries on the /bin folder
 * if none is found, it terminates itself
 */
pid_t instantiate(childp p);

// frees every dynamically allocated field from job
// including children, which was instantiated externally
void free_job(job m);

#endif // child

