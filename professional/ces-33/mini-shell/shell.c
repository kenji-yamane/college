#include <stdlib.h>

#include <unistd.h>
#include <signal.h>

#include "io/output.h"

#include "shell.h"

shell init_shell(shell s) {
    if (!isatty(STDIN_FILENO)) {
        usage_error("minishell does not support non interactive mode");
    }
    while (tcgetpgrp(STDIN_FILENO) != (s.pid = getpgrp())) {
        kill(-s.pid, SIGTTIN);
    }

    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGCHLD, SIG_IGN);

    s.pid = getpid();
    if (setpgid(s.pid, s.pid) < 0) {
        syscall_error("setgpid");
        exit(-1);
    }
    tcsetpgrp(STDIN_FILENO, s.pid);
    tcgetattr(STDIN_FILENO, &s.tmodes);
	return s;
}

