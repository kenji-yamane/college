#include <stdlib.h> // malloc | realloc
#include <string.h> // strcmp

#include "io/output.h" // developer_error | syntax_error
#include "processes/child.h" // new_child | add_argument | setters
#include "strings/strings.h" // count_words | extract_words

#include "parser.h"

childp *parse(char *str, int *num_children) {
	if (count_words(str) == 0) {
		*num_children = 0;
		return NULL;
	}
	char **words = extract_words(str);
	if (!syntax_check(words)) {
		*num_children = 0;
		free(words);
		return NULL;
	}
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

int syntax_check(char **words) {
	if (translate_operator(words[0]) != END) {
		syntax_error("first command cannot be an operator (<, > or |)");
		return 0;
	}

	for (int i = 1; words[i] != NULL; i++) {
		WORD prev, curr;
		prev = translate_operator(words[i - 1]);
		curr = translate_operator(words[i]);
		if (prev != END && curr != END) {
			syntax_error("consecutive operators");
			return 0;
		}
	}

	return 1;
}

WORD *translate(char **words) {
	WORD *translated = (WORD*)malloc(sizeof(WORD));
	translated[0] = PROGRAM;
	if (translate_operator(words[0]) != END) {
		translated[0] = END;
		return translated;
	}

	int i;
	for (i = 1; words[i] != NULL; i++) {
		translated = (WORD*)realloc(translated, (i + 1)*sizeof(WORD));
		translated[i] = translate_operator(words[i]);
		if (translated[i] == END) {
			translated[i] = filetype_from_operator(translated[i - 1]);
		}
	}
	translated = (WORD*)realloc(translated, (i + 1)*sizeof(WORD));
	translated[i] = END;

	return translated;
}

WORD translate_operator(char *w) {
	if (strcmp(w, "|") == 0) {
		return PIPE;
	} else if (strcmp(w, "<") == 0) {
		return LESS;
	} else if (strcmp(w, ">") == 0) {
		return GREATER;
	} else {
		return END;
	}
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
		return END;
	default:
		developer_error("filetype_from_operator expects a valid WORD");
	}
	return END;
}

