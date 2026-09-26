#include "../include/tokenizer.h"
#include "../include/datatypes.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int tokenize_string(const char *cursor, TokenArray token_array) {

  cursor++;
  const char *start = cursor;
  while (*cursor != '"' && *cursor != '\0') {
    cursor++;
  };
  size_t len = cursor - start;
  char *str_val = malloc(len + 1);
  if (str_val == NULL) {
    return 1;
  }
  strncpy(str_val, start, len);
  str_val[len] = '\0';
  if (*cursor == '"') {
    cursor++;
  };
  add_token(&cursor, &token_array,
            (Token){.type = TOKEN_STRING, .value = str_val});

  return 0;
}

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
  (*cursor)++;
  return 0;
}

int main_tokenizer(const char *sisu) {
  const char *cursor = sisu;
  TokenArray token_array = {.items = NULL, .size = 0, .capacity = 0};

  while (*cursor != '\0') {
    skip_whitespaces(&cursor);
    if (*cursor == '\0') {
      break;
    }

    char c = *cursor;

    switch (c) {
    case '{':
      add_token(&cursor, &token_array,
                (Token){.type = TOKEN_LCURLY, .value = "{"});
      break;
    case '}':
      add_token(&cursor, &token_array,
                (Token){.type = TOKEN_RCURLY, .value = "}"});
      break;

    case '(':
      add_token(&cursor, &token_array,
                (Token){.type = TOKEN_LBRACKET, .value = "("});
      break;
    case ')':
      add_token(&cursor, &token_array,
                (Token){.type = TOKEN_RBRACKET, .value = ")"});
      break;
    case ':':
      add_token(&cursor, &token_array,
                (Token){.type = TOKEN_COLON, .value = ":"});
      break;
    case ',':
      add_token(&cursor, &token_array,
                (Token){.type = TOKEN_COMA, .value = ","});
      break;
    case '"': {
      break;
    }
    };
  };
  return 0;
}
