#include <signal.h>

#include "builtin.h"

void minishell_exit(manager m) {
	free_manager(m);
	raise(SIGKILL);
}

manager minishell_process_info(manager m) {
	m = jobs_debrief(m);
	return m;
}

void minishell_foreground(shell s, manager m, int id) {
	int idx = get_job_idx_from_id(m, id);
	m.jobs[idx] = put_in_foreground(s, m.jobs[idx], true);
}

void minishell_background(manager m, int id) {
	int idx = get_job_idx_from_id(m, id);
	put_in_background(m.jobs[idx], true);
}

