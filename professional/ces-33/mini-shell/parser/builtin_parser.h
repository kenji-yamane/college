#ifndef BUILTIN_PARSER_H
#define BUILTIN_PARSER_H

#include "../processes/manager.h" // manager

typedef enum{
	EXIT,
	DEBRIEF,
	FOREGROUND,
	BACKGROUND,
	UNDEFINED
} BUILTIN;

// parses a line command into one of minishell's builtin commands
// if none fits, returns UNDEFINED
BUILTIN parse_builtin(char *str);

// executes a given builtin
manager execute_builtin(shell s, manager m, char *str, BUILTIN b);

// returns a pointer to the first non-space character,
// without allocating new memory
char *trim_begin(char *str);

// gets job_id from a job control argument
// returns -1 if scan failed
int scan_job_id(char *str);

#endif

