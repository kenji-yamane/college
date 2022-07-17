#include <signal.h>

#include "../io/output.h"
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
	if (idx == -1) {
		usage_error("no such job");
		return;
	}
	continue_job(s, m, idx, true);
}

void minishell_background(shell s, manager m, int id) {
	int idx = get_job_idx_from_id(m, id);
	if (idx == -1) {
		usage_error("no such job");
		return;
	}
	continue_job(s, m, idx, false);
}

