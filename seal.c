#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void error(int c) {
	printf("Error: ");
	if (c == 1) {
		puts("The input is empty.");
	}
	exit(1);
}

int main(int argc, char* argv[]) {
	system("@cls||clear");
	char space[1000];
	FILE *file;
	if ((file = fopen(argv[1], "r")) == NULL) {
		error(1);
	}
	fscanf(file, "%[^\n]", space);
	if (strchr(space, 'say(') != NULL) {
		int torem = strlen(space) - 5;
		space[strlen(space)-1] = '\0';
		printf("%s\n", space + strlen(space) - torem);
	}
	fclose(file);
	return 0;
}