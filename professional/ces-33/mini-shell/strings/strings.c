#include <string.h> // strlen | strcpy | strcat
#include <ctype.h> // isspace
#include <stdlib.h> // malloc | realloc | NULL

#include "strings.h"

char *prepend(char *prefix, char *str) {
	char *result = (char*)malloc((strlen(prefix)+strlen(str)+1)*sizeof(char));
	strcpy(result, prefix);
	strcat(result, str);
	return result;
}

int count_words(char *str) {
	int len = strlen(str), numw = 0;

	int space = 1;
	for (int i = 0; i < len; i++) {
		if (space && !isspace(str[i])) {
			numw++;
		}
		space = isspace(str[i]);
	}
	return numw;
}

char **extract_words(char *str) {
	int numw = count_words(str), len = strlen(str);
	char **words = (char**)malloc((numw + 1)*sizeof(char*));

	int space = 1;
	for (int i = 0, j = 0; i < len; i++) {
		int first_letter = (space && !isspace(str[i]));
		int first_space = (!space && isspace(str[i]));
		space = isspace(str[i]);
		if (first_letter) {
			words[j++] = str + i;
		}
		if (first_space) {
			str[i] = '\0';
		}
	}
	words[numw] = NULL;
	return words;
}

