#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int read_from_file(char *filename);
void skip_whitespaces(const char **cursor);
int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Not enough args");
    return 1;
  }
  read_from_file(argv[1]);

  return 0;
}
