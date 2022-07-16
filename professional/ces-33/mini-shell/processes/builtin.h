#ifndef BUILTIN_H
#define BUILTIN_H

#include "child.h"
#include "manager.h"

// builtin command to kill itself
void minishell_exit(manager m);

// builtin command to notify about jobs
manager minishell_process_info(manager m);

#endif

