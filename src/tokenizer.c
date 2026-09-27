#include "../include/tokenizer.h"
#include "../include/datatypes.h"
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_tokens(TokenArray token_array) {
  for (size_t i = 0; i < token_array.size; i++) {
    printf("Token %zu -> Type: %d, Value: \"%s\"\n", i,
           token_array.items[i].type, token_array.items[i].value);
  }
}

int tokenize_num(const char **cursor_ptr, TokenArray *token_array) {

  const char *start = *cursor_ptr;
  const char *cursor = start;

  if (*cursor == '-') {
    cursor++;
  }

  while (isdigit(*cursor)) {
    cursor++;
  };

  if (*cursor == '.') {
    cursor++;
  };

  if (*cursor == 'e' || *cursor == 'E') {
    cursor++;
    if (*cursor == '+' || *cursor == '-')
      cursor++;
    while (isdigit(*cursor))
      cursor++;
  };

  size_t len = cursor - start;
  char *num_val = malloc(len + 1);
  if (num_val == NULL) {
    return 1;
  };

  strncpy(num_val, start, len);
  num_val[len] = '\0';

  *cursor_ptr = cursor;

  add_token(token_array, (Token){.type = TOKEN_NUMBER, .value = num_val});

  return 0;
}

int tokenize_string(const char **cursor_ptr, TokenArray *token_array) {

  const char *cursor = *cursor_ptr + 1;
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
  *cursor_ptr = cursor;
  add_token(token_array, (Token){.type = TOKEN_STRING, .value = str_val});

  return 0;
}

void skip_whitespaces(const char **cursor) {
  while (**cursor == ' ' || **cursor == '\t' || **cursor == '\n') {
    (*cursor)++;
  }
}

int add_token(TokenArray *token_array, Token new_token) {
  if (token_array->size == token_array->capacity) {
    size_t new_capacity =
        (token_array->capacity == 0) ? 8 : token_array->capacity * 2;
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
      add_token(&token_array, (Token){.type = TOKEN_LCURLY, .value = "{"});
      cursor++;
      break;
    case '}':
      add_token(&token_array, (Token){.type = TOKEN_RCURLY, .value = "}"});
      cursor++;
      break;

    case '(':
      add_token(&token_array, (Token){.type = TOKEN_LBRACKET, .value = "("});
      cursor++;
      break;
    case ')':
      add_token(&token_array, (Token){.type = TOKEN_RBRACKET, .value = ")"});
      cursor++;
      break;
    case ':':
      add_token(&token_array, (Token){.type = TOKEN_COLON, .value = ":"});
      cursor++;
      break;
    case ',':
      add_token(&token_array, (Token){.type = TOKEN_COMA, .value = ","});
      cursor++;
      break;
    case '"': {
      tokenize_string(&cursor, &token_array);
      break;
    }
    default:

      if (strncmp(cursor, "true", 4) == 0) {
        add_token(&token_array, (Token){.type = TOKEN_BOOL, .value = "true"});
        cursor += 4;
      } else if (strncmp(cursor, "false", 5) == 0) {
        add_token(&token_array, (Token){.type = TOKEN_BOOL, .value = "false"});
        cursor += 5;
      }

      else if (strncmp(cursor, "null", 4) == 0) {
        add_token(&token_array, (Token){.type = TOKEN_NULL, .value = "null"});
        cursor += 4;
      } else if (isdigit(c) || c == '-') {
        tokenize_num(&cursor, &token_array);
      } else {
        cursor++;
      }
    };
  };
  print_tokens(token_array);
  return 0;
}
