#include <stdlib.h> // NULL
#include <sys/wait.h> // waitpid

#include "strings/strings.h" // extract_words
#include "io/output.h" // welcome_message | prompt
#include "io/input.h" // read_line
#include "child_registry/child.h" // childp_create

#include <stdio.h>

int main() {
	welcome_message();
	while (1) {
		prompt();

		char *str = read_line();
		char **words = extract_words(str);
		for (int i = 0; words[i] != NULL; i++) {
			printf("[DEBUG] %s\n", words[i]);
		}
		childp p = childp_create(words[0]);
		waitpid(p.pid, NULL, 0);
		free(str);
		free(words);
	}
	return 0;
}

