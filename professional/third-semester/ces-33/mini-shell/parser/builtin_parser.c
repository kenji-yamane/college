#include <string.h> // strcmp
#include <stdlib.h> // atoi

#include "../io/output.h" // developer_error
#include "../strings/strings.h"
#include "../processes/builtin.h" // minishell_exit

#include "builtin_parser.h"

BUILTIN parse_builtin(char *str) {
	char *trimmed = trim_end(trim_begin(str));
	if (strcmp(trimmed, "exit") == 0) {
		return EXIT;
	} else if (strcmp(trimmed, "jobs") == 0) {
		return DEBRIEF;
	} else if (strlen(trimmed) > 1 && trimmed[0] == 'f' && trimmed[1] == 'g') {
		return FOREGROUND;
	} else if (strlen(trimmed) > 1 && trimmed[0] == 'b' && trimmed[1] == 'g') {
		return BACKGROUND;
	}
	return UNDEFINED;
}

manager execute_builtin(shell s, manager m, char *str, BUILTIN b) {
	int job_id;
	char *trimmed = trim_end(trim_begin(str));
	switch (b) {
	case EXIT:
		minishell_exit(m);
		break;
	case DEBRIEF:
		m = minishell_process_info(m);
		break;
	case FOREGROUND:
		job_id = scan_job_id(trimmed + 2);
		if (job_id == -1) {
			syntax_error("fg accepts only one integer argument preceded by %");
		} else {
			minishell_foreground(s, m, job_id);
		}
		break;
	case BACKGROUND:
		job_id = scan_job_id(trimmed + 2);
		if (job_id == -1) {
			syntax_error("bg accepts only one integer argument preceded by %");
		} else {
			minishell_background(s, m, job_id);
		}
		break;
	case UNDEFINED:
		developer_error("UNDEFINED does not match a builtin");
		break;
	}
	return m;
}

int scan_job_id(char *str) {
	char *trimmed = trim_begin(str);
	if (strlen(trimmed) == 0) {
		return -1;
	}
	if (trimmed[0] != '%') {
		return -1;
	}
	trimmed++;
	if (strlen(trimmed) == 0) {
		return -1;
	}
	if (!is_number(trimmed)) {
		return -1;
	}
	return atoi(trimmed);
}

