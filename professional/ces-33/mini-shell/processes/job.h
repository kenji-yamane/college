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

// pipes ith child's output to its successor's input
void connect_children(job j);

// prints job's status with descriptive messages
// and references
void print_job_info(job j, char *status_name);

// uses print_job_info with status completed
void notify_completed_job(job j);

// uses print_job_info with status stopped
job notify_stopped_job(job j);

// uses print_job_info with status running
void notify_running_job(job j);

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

