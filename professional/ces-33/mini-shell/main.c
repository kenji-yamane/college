#include <stdlib.h> // free

#include "io/output.h" // welcome_message | prompt
#include "io/input.h" // read_line
#include "parser/parser.h" // parse
#include "parser/builtin_parser.h"
#include "processes/job.h" // create_job | connect_children | execute_children | free_job
#include "processes/manager.h"
#include "shell.h" // init_shell
#include "strings/strings.h" // copy_str

int main() {
	shell s = init_shell(s);
	manager m = init_manager();

	welcome_message();
	while (1) {
		m = notify_job_events(m);
		prompt();

		char *str = read_line();
		char *backup_str = copy_str(str);
		BUILTIN b = parse_builtin(str);
		if (b != UNDEFINED) {
			m = execute_builtin(s, m, str, b);
			free(str);
			free(backup_str);
			continue;
		}
		int num_children;
		childp *children = parse(str, &num_children);
		if (num_children == 0) {
			continue;
		}

		job j = create_job(num_children, children, backup_str);
		connect_children(j);
		j = execute_children(s, j, true);
		m = insert_job(m, j);

		free(str);
	}

	free_manager(m);
	return 0;
}

