#include "../include/tokenizer.h"
#include "../include/datatypes.h"
#include <stddef.h>
#include <stdlib.h>

void skip_whitespaces(const char **cursor) {
  while (**cursor == ' ' || **cursor == '\t' || **cursor == '\n') {
    (*cursor)++;
  }
}

int add_token(const char **cursor, TokenArray *token_array, Token new_token) {
  if (token_array->size == token_array->capacity) {
    size_t new_capacity = token_array->capacity * 2;
    Token *tmp = realloc(token_array->items, sizeof(Token) * new_capacity);
    if (tmp == NULL) {
      return 1;
    }

    token_array->items = tmp;
    token_array->capacity = new_capacity;
  }

  token_array->items[token_array->size] = new_token;
  token_array->size++;
  return 0;
}

void main_tokenizer(const char *sisu) {
  const char *cursor = sisu;
  TokenArray token_array = {.items = NULL, .size = 0, .capacity = 0};

  while (*cursor != '\0') {
    skip_whitespaces(&cursor);

    char c = *cursor;

    switch (c) {
    case '{':
      add_token(&cursor, &token_array,
                (Token){.type = TOKEN_LCURLY, .value = NULL});
      break;
    }

    if (*cursor == '\0') {
      break;
    }
  }
}
