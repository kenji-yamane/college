#include <stdio.h> // getchar
#include <stdlib.h> // realloc

#include "input.h"

char *read_line() {
	char *line = (char*)malloc(sizeof(char));
	int numc = 0;
	do {
		line = (char*)realloc(line, (numc + 1)*sizeof(char));
		line[numc] = getchar();
		numc++;
	} while (line[numc - 1] != '\n');
	line[numc - 1] = '\0';
	return line;
}

