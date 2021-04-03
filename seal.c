#include <stdlib.h>
#include <stdio.h>
#include <string.h>

fpos_t pos;

void error(int c) {
  printf("Error: ");
  if (c == 1) {
    puts("The input is empty.");
  }
  exit(1);
}

int main(int argc, char* argv[]) {
  system("clear");
  char space[100];
  FILE *file;
  if ((file = fopen(argv[1], "r")) == NULL) {
    error(1);
  }
  while (fscanf(file, "say(%[^\n)]", space)) {
    puts(space);
    getc(file);
    if (feof(file)) {
      break;
    } 
  }
  fclose(file);
  return 0;
}