#include <stdlib.h> // free

#include "io/output.h" // welcome_message | prompt
#include "io/input.h" // read_line
#include "parser/parser.h" // parse
#include "parser/builtin_parser.h"
#include "processes/job.h" // create_job | connect_children | execute_children | free_job
#include "shell.h" // init_shell
#include "strings/strings.h" // copy_str

int main() {
	shell s;
	s = init_shell(s);

	welcome_message();
	while (1) {
		prompt();

		char *str = read_line();
		char *backup_str = copy_str(str);
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

		job j = create_job(num_children, children, backup_str);
		connect_children(j);
		execute_children(s, j, true);

		free_job(j);
		free(str);
	}
	return 0;
}

