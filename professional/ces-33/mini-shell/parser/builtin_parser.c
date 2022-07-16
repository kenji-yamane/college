#include <string.h> // strcmp

#include "../io/output.h" // developer_error
#include "../processes/builtin.h" // minishell_exit

#include "builtin_parser.h"

BUILTIN parse_builtin(char *str) {
	if (strcmp(str, "exit") == 0) {
		return EXIT;
	}
	return UNDEFINED;
}

void execute_builtin(BUILTIN b) {
	switch (b) {
	case EXIT:
		minishell_exit();
		break;
	case UNDEFINED:
		developer_error("UNDEFINED does not match a builtin");
		break;
	}
}

