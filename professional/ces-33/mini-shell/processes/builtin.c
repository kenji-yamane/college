#include <signal.h>

#include "builtin.h"

void minishell_exit() {
	raise(SIGKILL);
}

manager minishell_process_info(manager m) {
	m = jobs_debrief(m);
	return m;
}

