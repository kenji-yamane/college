#ifndef BUILTIN_PARSER_H
#define BUILTIN_PARSER_H

#include "../processes/manager.h" // manager

typedef enum{
	EXIT,
	DEBRIEF,
	FOREGROUND,
	UNDEFINED
} BUILTIN;

// parses a line command into one of minishell's builtin commands
// if none fits, returns UNDEFINED
BUILTIN parse_builtin(char *str);

// executes a given builtin
manager execute_builtin(shell s, manager m, char *str, BUILTIN b);

#endif

