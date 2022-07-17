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
manager init_manager();

// puts job in foreground, letting it assume the terminal
void put_in_foreground(shell s, manager m, int idx, bool cont);

// puts job in background, removing it from the terminal
void put_in_background(manager m, int idx, bool cont);

// resets notified flag and children's stopped flags to false
// and then continues the job on the background or the foreground
// accordingly
void continue_job(shell s, manager m, int idx, bool foregroud);

// instantiates each child sequentially, waiting
// for the end of the ith child to close its
// output and then instantiate the successor
void execute_children(shell s, manager m, int idx, bool foreground);

// inserts an executed job in manager structure,
// so that we can track it
manager insert_job(manager m, job j);

// gets the job index on the manager structure
// given its id using binary search
int get_job_idx_from_id(manager m, int id);

// frees a job given its index, and then removes it
// from the data structure, using the unshift algorithm
manager remove_job(manager m, int idx);

// notifies jobs that have either stopped or completed
// deleting from its structure those that have completed
manager notify_job_events(manager m);

// notifies every job, with its current status
manager jobs_debrief(manager m);

// updates status on all processes of all jobs the manager
// holds
void update_all_processes(manager m);

// given a pid and a status, it searches for a process with this
// given pid and parses its status. It returns -1 if it
// doesn't find a corresponding child, and 0 on success
int mark_process_status(manager m, pid_t pid, int status);

// frees every dynamically allocated field from manager
// including jobs, which was instantiated externally
void free_manager(manager m);

#endif // manager

