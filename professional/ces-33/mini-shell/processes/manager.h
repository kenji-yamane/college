#ifndef MANAGER_H
#define MANAGER_H

#include <sys/types.h>

#include "job.h"

/*
 * manager holds the set of all
 * jobs that have not terminated
 */
typedef struct {
    job *jobs;
	int sequential;
	int num_jobs;
	int num_allocated;
} manager;

// instantiates a manager structure, setting
// its initial id to zero
manager init_jobs();

// inserts an executed job in manager structure,
// so that we can track it
manager insert_job(manager m, job j);

// frees a job given its index, and then removes it
// from the data structure
manager remove_job(manager m, int idx);

// notifies jobs that have either stopped or completed
// deleting from its structure those that have completed
manager jobs_debrief(manager m);

// updates status on all processes of all jobs the manager
// holds
void update_all_processes(manager m);

// given a pid and a status, it searches for a process with this
// given pid and parses its status. It returns -1 if it
// doesn't find a corresponding child, and 0 on success
int mark_process_status(manager m, pid_t pid, int status);

#endif // manager

