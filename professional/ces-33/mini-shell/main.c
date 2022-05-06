#include <stdlib.h> // free

#include "io/output.h" // welcome_message | prompt
#include "io/input.h" // read_line
#include "parser.h" // parse
#include "processes/manager.h" // create_manager | connect_children | execute_children | free_manager

int main() {
	welcome_message();
	while (1) {
		prompt();

		char *str = read_line();
		int num_children;
		childp *children = parse(str, &num_children);
		if (num_children == 0) {
			continue;
		}

		pmanager m = create_pmanager(num_children, children);
		connect_children(m);
		execute_children(m);

		free_manager(m);
		free(str);
	}
	return 0;
}

