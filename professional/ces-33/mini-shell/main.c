#include <stdlib.h> // free

#include "io/output.h" // welcome_message | prompt
#include "io/input.h" // read_line
#include "parser/parser.h" // parse
#include "parser/builtin_parser.h"
#include "processes/job.h" // create_job | connect_children | execute_children | free_job
#include "shell.h" // init_shell

int main() {
	shell s;
	s = init_shell(s);

	welcome_message();
	while (1) {
		prompt();

		char *str = read_line();
		BUILTIN b = parse_builtin(str);
		if (b != UNDEFINED) {
			free(str);
			execute_builtin(b);
			continue;
		}
		int num_children;
		childp *children = parse(str, &num_children);
		if (num_children == 0) {
			continue;
		}

		job m = create_job(num_children, children);
		connect_children(m);
		execute_children(m);

		free_job(m);
		free(str);
	}
	return 0;
}

