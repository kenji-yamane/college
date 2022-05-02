#ifndef PARSER_H
#define PARSER_H

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

childp *parse(char *str, int *num_children);

WORD *translate(char **words);

#endif

