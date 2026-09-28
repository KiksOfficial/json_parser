#include "include/datatypes.h"
#include "include/parser.h"
#include "include/read_file.h"
#include "include/tokenizer.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Not enough args");
    return 1;
  }
  const char *sisu = read_from_file(argv[1]);
  TokenArray tokens = main_tokenizer(sisu);
  print_tokens(tokens);

  return 0;
}
