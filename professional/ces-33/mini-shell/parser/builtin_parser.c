#include <string.h> // strcmp
#include <stdio.h>

#include "../io/output.h" // developer_error
#include "../processes/builtin.h" // minishell_exit

#include "builtin_parser.h"

BUILTIN parse_builtin(char *str) {
	if (strcmp(str, "exit") == 0) {
		return EXIT;
	} else if (strcmp(str, "jobs") == 0) {
		return DEBRIEF;
	} else if (strlen(str) > 1 && str[0] == 'f' && str[1] == 'g') {
		return FOREGROUND;
	} else if (strlen(str) > 1 && str[0] == 'b' && str[1] == 'g') {
		return BACKGROUND;
	}
	return UNDEFINED;
}

manager execute_builtin(shell s, manager m, char *str, BUILTIN b) {
	int job_id;
	switch (b) {
	case EXIT:
		minishell_exit(m);
		break;
	case DEBRIEF:
		m = minishell_process_info(m);
		break;
	case FOREGROUND:
		if (!sscanf(str, "fg %%%d", &job_id)) {
			syntax_error("fg accepts only one integer argument preceded by %%");
			break;
		}
		minishell_foreground(s, m, job_id);
		break;
	case BACKGROUND:
		if (!sscanf(str, "bg %%%d", &job_id)) {
			syntax_error("bg accepts only one integer argument preceded by %%");
			break;
		}
		minishell_background(m, job_id);
		break;
	case UNDEFINED:
		developer_error("UNDEFINED does not match a builtin");
		break;
	}
	return m;
}

