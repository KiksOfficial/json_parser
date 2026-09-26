#ifndef TOKNIZER_H
#define TOKNIZER_H
#include "datatypes.h"

void skip_whitespaces(const char **cursor);
int main_tokenizer(const char *sisu);
int add_token(const char **cursor, TokenArray *token_array, Token new_token);

#endif
