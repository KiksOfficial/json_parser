#ifndef DATATYPES_H
#define DATATYPES_H
#include <stddef.h>
#include <stdio.h>

typedef enum ValueType {
  JSON_NULL,
  JSON_BOOL,
  JSON_STRING,
  JSON_NUMBER,
  JSON_OBJE,
  JSON_ARRAY,

} ValueType;

typedef enum TokenType {
  TOKEN_LCURLY,
  TOKEN_RCURLY,
  TOKEN_LBRACKET,
  TOKEN_RBRACKET,
  TOKEN_COLON,
  TOKEN_COMA,
  TOKEN_STRING,
  TOKEN_NUMBER,
  TOKEN_BOOL,
  TOKEN_NULL,
  TOKEN_EOF
} TokenType;

typedef struct JSONValue JSONValue;

struct JSONValue {
  ValueType type;
  union {
    double num;
    int boolean;
    char *str;
  } data;

  struct {
    JSONValue **items;
    size_t count;
  } array;
};

typedef struct {
  TokenType type;
  const char *value;
} Token;

typedef struct {
  Token *items;
  size_t size;
  size_t capacity;
} TokenArray;

#endif
