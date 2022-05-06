#include <stdlib.h> // malloc | realloc
#include <string.h> // strcmp

#include "io/output.h" // developer_error
#include "processes/child.h" // new_child | add_argument | setters
#include "strings/strings.h" // extract_words

#include "parser.h"

childp *parse(char *str, int *num_children) {
	char **words = extract_words(str);
	WORD *translation = translate(words);

	int numc = 1;
	childp *children = (childp*)malloc(sizeof(childp));
	children[0] = new_child();
	children[0] = add_argument(children[0], words[0]);
	for (int i = 1; translation[i] != END; i++) {
		switch (translation[i]) {
		case PROGRAM:
			numc++;
			children = (childp*)realloc(children, numc*sizeof(childp));
			children[numc - 1] = new_child();
			children[numc - 1] = add_argument(children[numc - 1], words[i]);
			break;
		case ARGUMENT:
			children[numc - 1] = add_argument(children[numc - 1], words[i]);
			break;
		case INPUT_FILE:
			set_input_file(children[numc - 1], words[i]);
			break;
		case OUTPUT_FILE:
			set_output_file(children[numc - 1], words[i]);
			break;
		case PIPE:
		case LESS:
		case GREATER:
		default:
			break;
		}
	}
	*num_children = numc;

	free(translation);
	free(words);

	return children;
}

WORD *translate(char **words) {
	WORD *translated = (WORD*)malloc(sizeof(WORD));
	translated[0] = PROGRAM;

	int i;
	for (i = 1; words[i] != NULL; i++) {
		translated = (WORD*)realloc(translated, (i + 1)*sizeof(WORD));
		if (strcmp(words[i], "|") == 0) {
			translated[i] = PIPE;
		} else if (strcmp(words[i], "<") == 0) {
			translated[i] = LESS;
		} else if (strcmp(words[i], ">") == 0) {
			translated[i] = GREATER;
		} else {
			translated[i] = filetype_from_operator(translated[i - 1]);
		}
	}
	translated = (WORD*)realloc(translated, (i + 1)*sizeof(WORD));
	translated[i] = END;

	return translated;
}

WORD filetype_from_operator(WORD w) {
	switch (w) {
	case PIPE:
		return PROGRAM;
	case LESS:
		return INPUT_FILE;
	case GREATER:
		return OUTPUT_FILE;
	case PROGRAM:
	case ARGUMENT:
	case INPUT_FILE:
	case OUTPUT_FILE:
		return ARGUMENT;
	case END:
		developer_error("filetype_from_operator does not accept END label");
	default:
		developer_error("filetype_from_operator expects a valid WORD");
	}
	return END;
}

