#ifndef JOB_H
#define JOB_H

#include <sys/types.h> // pid_t
#include <termios.h>

#include <stdbool.h>

#include "child.h"
#include "../shell.h"

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
	char *command;
	int pgid;
	struct termios tmodes;
	int id;
	bool notified;
} job;

// instantiates a job structure, allocating space for
// the arrays that will contain metadata relative to
// the created processes
job create_job(int num_processes, childp *children, char *command);

// puts job in foreground, letting it assume the terminal
job put_in_foreground(shell s, job j, bool cont);

// puts job in background, removing it from the terminal
void put_in_background(job j, bool cont);

// waits for all job's processes
void wait_job(job j);

// pipes ith child's output to its successor's input
void connect_children(job j);

// instantiates each child sequentially, waiting
// for the end of the ith child to close its
// output and then instantiate the successor
job execute_children(shell s, job j, bool foreground);

// prints job's status with descriptive messages
// and references
void print_job_info(job j, char *status_name);

// uses print_job_info with status completed
void notify_completed_job(job j);

// uses print_job_info with status stopped
job notify_stopped_job(job j);

// asserts whether all of the job's processes
// have either stopped or completed
bool job_stopped(job j);

// asserts whether all of the job's processes
// have completed
bool job_completed(job j);

// frees every dynamically allocated field from job
// including children, which was instantiated externally
void free_job(job j);

#endif // job

