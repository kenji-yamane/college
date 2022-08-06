#ifndef BUILTIN_H
#define BUILTIN_H

#include "child.h"
#include "manager.h"

// builtin command to kill itself
void minishell_exit(manager m);

// builtin command to notify about jobs
manager minishell_process_info(manager m);

// builtin command to bring a background process
// to the foreground
void minishell_foreground(shell s, manager m, int id);

// builtin command to continue a stopped process
// on the background
void minishell_background(shell s, manager m, int id);

#endif

