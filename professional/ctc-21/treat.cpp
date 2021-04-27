#include <bits/stdc++.h>

int main(int argc, char *argv[]) {
	FILE *e = fopen("questao10.pl", "r");
	FILE *s = fopen("output.pl", "w");
	char str[100], newvars[13][100], movie[100];

	for (int i = 0; i < 13; i++) {
		scanf(" %s", newvars[i]);
	}

	for (int i = 0; i < 13; i++) {
		fgets(str, 100, e);
		sscanf(str, "%*[^(](%s", movie);
		fprintf(s, "%s(%s %s).\n", argv[1], movie, newvars[i]);
	}

	fclose(e);
	fclose(s);

	return 0;
}

