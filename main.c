#include "include/read_file.h"
#include "include/tokenizer.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Not enough args");
    return 1;
  }
  const char *sisu = read_from_file(argv[1]);
  main_tokenizer(sisu);

  return 0;
}
