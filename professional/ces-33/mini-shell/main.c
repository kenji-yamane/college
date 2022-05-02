#include <stdlib.h> // NULL
#include <sys/wait.h> // waitpid
#include <sys/types.h> // pid_t
#include <unistd.h> // pipe | close

#include "io/output.h" // welcome_message | prompt
#include "io/input.h" // read_line
#include "child_registry/child.h" // childp_create
#include "parser.h" // parse

int main() {
	welcome_message();
	while (1) {
		prompt();

		char *str = read_line();
		int num_children;
		// TODO: create processor master in child_registry/
		childp *p = parse(str, &num_children);
		if (num_children == 0) {
			continue;
		}

		// TODO: replace VLA with pointers
		int pipes[num_children][2];
		for (int i = 1; i < num_children; i++) {
			pipe(pipes[i]);
			p[i - 1].pipe_out = pipes[i][1];
			p[i].pipe_in = pipes[i][0];
		}
		for (int i = 0; i < num_children; i++) {
			pid_t pid = childp_create(p[i]);
			int status;
			waitpid(pid, &status, 0);
			if (i < num_children - 1) {
				close(pipes[i + 1][1]);
			}
		}
		free(str);
		for (int i = 0; i < num_children; i++) {
			free_child(p[i]);
		}
	}
	return 0;
}

