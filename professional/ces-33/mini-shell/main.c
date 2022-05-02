#include <stdlib.h> // NULL
#include <sys/wait.h> // waitpid
#include <sys/types.h> // pid_t

#include "io/output.h" // welcome_message | prompt
#include "io/input.h" // read_line
#include "child_registry/child.h" // childp_create
#include "parser.h" // parse

#include <stdio.h>

int main() {
	welcome_message();
	while (1) {
		prompt();

		char *str = read_line();
		int num_children;
		childp *p = parse(str, &num_children);
		if (num_children == 0) {
			continue;
		}
		for (int i = 0; i < num_children; i++) {
			pid_t pid = childp_create(p[i]);
			waitpid(pid, NULL, 0);
		}
		free(str);
	}
	return 0;
}

