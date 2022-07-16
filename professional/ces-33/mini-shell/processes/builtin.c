#include <signal.h>

#include "builtin.h"

void minishell_exit() {
	raise(SIGKILL);
}

