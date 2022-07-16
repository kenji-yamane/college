#ifndef PARSER_H
#define PARSER_H

#include "processes/child.h"

typedef enum{
	PROGRAM,
	ARGUMENT,
	PIPE,
	LESS,
	GREATER,
	INPUT_FILE,
	OUTPUT_FILE,
	END
} WORD;

typedef enum{
	EXIT,
	UNDEFINED
} BUILTIN;

// parses a line command into one of minishell's builtin commands
// if none fits, returns UNDEFINED
BUILTIN parse_builtin(char *str);

// executes a given builtin
void execute_builtin(BUILTIN b);

// parses a line command into a sequence of children to be instantiated as processes
childp *parse(char *str, int *num_children);

// checks syntax, returning a positive number if everything is ok and 0 otherwise
// prints a corresponding error if something is wrong
int syntax_check(char **words);

// labels each word with a WORD enum
WORD *translate(char **words);

// labels w with either PIPE, GREATER or LESS
// if neither fits, returns END
WORD translate_operator(char *w);

// deduces a filetype based on the previous word:
// preceded by PIPE: PROGRAM
// preceded by LESS: INPUT_FILE
// preceded by GREATER: OUTPUT_FILE
WORD filetype_from_operator(WORD w);


#endif

