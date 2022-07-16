#include <stdlib.h> // free

#include <sys/types.h> // pid_t
#include <termios.h> // struct termios
#include <unistd.h>
#include <signal.h>

#include "io/output.h" // welcome_message | prompt
#include "io/input.h" // read_line
#include "parser.h" // parse
#include "processes/job.h" // create_job | connect_children | execute_children | free_job

// awaits for the job to be on foreground, and then ignores all
// job control signals, proceeding to set itself as its own
// process group and take control of the terminal, saving
// the terminal modes
void init_shell(pid_t *pid, struct termios *tmodes);

int main() {
	pid_t shell_pgid;
	struct termios shell_tmodes;
	init_shell(&shell_pgid, &shell_tmodes);

	welcome_message();
	while (1) {
		prompt();

		char *str = read_line();
		BUILTIN b = parse_builtin(str);
		if (b != UNDEFINED) {
			free(str);
			execute_builtin(b);
			continue;
		}
		int num_children;
		childp *children = parse(str, &num_children);
		if (num_children == 0) {
			continue;
		}

		job m = create_job(num_children, children);
		connect_children(m);
		execute_children(m);

		free_job(m);
		free(str);
	}
	return 0;
}

void init_shell(pid_t *pid, struct termios *tmodes) {
	if (!isatty(STDIN_FILENO)) {
		usage_error("minishell does not support non interactive mode");
	}
	while (tcgetpgrp(STDIN_FILENO) != (*pid = getpgrp())) {
		kill(-(*pid), SIGTTIN);
	}

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);

	*pid = getpid();
	if (setpgid(*pid, *pid) < 0) {
		syscall_error("setgpid");
		exit(-1);
	}
	tcsetpgrp(STDIN_FILENO, *pid);
	tcgetattr(STDIN_FILENO, tmodes);
}

