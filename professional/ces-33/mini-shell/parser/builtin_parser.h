#ifndef BUILTIN_PARSER_H
#define BUILTIN_PARSER_H

typedef enum{
	EXIT,
	UNDEFINED
} BUILTIN;

// parses a line command into one of minishell's builtin commands
// if none fits, returns UNDEFINED
BUILTIN parse_builtin(char *str);

// executes a given builtin
void execute_builtin(BUILTIN b);

#endif

