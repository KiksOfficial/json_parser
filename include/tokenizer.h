#ifndef TOKNIZER_H
#define TOKNIZER_H
#include "datatypes.h"

void skip_whitespaces(const char **cursor);
TokenArray main_tokenizer(const char *sisu);
int add_token(TokenArray *token_array, Token new_token);
void print_tokens(TokenArray token_array);

#endif
