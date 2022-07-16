#include <string.h> // strcmp

#include "../io/output.h" // developer_error
#include "../processes/builtin.h" // minishell_exit

#include "builtin_parser.h"

BUILTIN parse_builtin(char *str) {
	if (strcmp(str, "exit") == 0) {
		return EXIT;
	} else if (strcmp(str, "jobs") == 0) {
		return DEBRIEF;
	}
	return UNDEFINED;
}

manager execute_builtin(manager m, BUILTIN b) {
	switch (b) {
	case EXIT:
		minishell_exit(m);
		break;
	case DEBRIEF:
		m = minishell_process_info(m);
		break;
	case UNDEFINED:
		developer_error("UNDEFINED does not match a builtin");
		break;
	}
	return m;
}

