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

int read_from_file(char *filename) {

  FILE *fptr = fopen(filename, "r");

  if (fptr == NULL) {
    printf("Couldn't open file");
    return 1;
  }

  fseek(fptr, 0, SEEK_END);
  long file_size = ftell(fptr);
  fseek(fptr, 0, SEEK_SET);

  char *content_buff = malloc(file_size + 1);

  if (content_buff == NULL) {
    fclose(fptr);
    return 1;
  }

  size_t byteas_read = fread(content_buff, sizeof(char), file_size, fptr);
  content_buff[byteas_read] = '\0';

  printf("%s", content_buff);

  fclose(fptr);
  free(content_buff);
  content_buff = NULL;

  return 0;
}

void skip_whitespaces(const char **cursor) {
  while (**cursor == ' ' || **cursor == '\t' || **cursor == '\n') {
    cursor++;
  }
}
