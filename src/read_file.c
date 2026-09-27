#include "../include/read_file.h"
#include <stdio.h>
#include <stdlib.h>
char *read_from_file(char *filename) {

  FILE *fptr = fopen(filename, "r");

  if (fptr == NULL) {
    printf("Couldn't open file");
    return NULL;
  }

  fseek(fptr, 0, SEEK_END);
  long file_size = ftell(fptr);
  fseek(fptr, 0, SEEK_SET);

  char *content_buff = malloc(file_size + 1);

  if (content_buff == NULL) {
    fclose(fptr);
    return NULL;
  }

  size_t byteas_read = fread(content_buff, sizeof(char), file_size, fptr);
  content_buff[byteas_read] = '\0';

  fclose(fptr);
  return content_buff;
}
