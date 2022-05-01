#include <stdlib.h> // NULL
#include <sys/wait.h> // waitpid

#include "child_registry/child.h" // childp_create
#include "io/output.h" // welcome_message | prompt
#include "io/input.h" // read_line

int main() {
	welcome_message();
	while (1) {
		prompt();

		char *str = read_line();
		childp p = childp_create(str);
		waitpid(p.pid, NULL, 0);
	}
	return 0;
}

