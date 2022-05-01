#include <stdio.h> // getchar
#include <stdlib.h> // realloc

#include "child_registry/child.h"
#include "io/output.h"
#include <sys/wait.h>

int main() {
	welcome_message();
	while (1) {
		prompt();

		int numc = 0;
		char *str;
		do {
			str = (char*)realloc(str, (numc + 1)*sizeof(char));
			str[numc] = getchar();
			numc++;
		} while (str[numc - 1] != '\n');
		str[numc - 1] = '\0';

		childp p = childp_create(str);
		waitpid(p.pid, NULL, 0);
	}
	return 0;
}

