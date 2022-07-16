#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h> // pid_t
#include <termios.h> // struct termios

typedef struct {
	pid_t pid;
	struct termios tmodes;
} shell;

// awaits for the job to be on foreground, and then ignores all
// job control signals, proceeding to set itself as its own
// process group and take control of the terminal, saving
// the terminal modes
shell init_shell(shell s);

#endif

