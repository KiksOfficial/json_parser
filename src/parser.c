#include "../include/parser.h"
#include "../include/datatypes.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

JSONValue *parse_object(TokenArray *tokens, size_t *index) {
  (*index)++;
  JSONValue *obj_node = malloc(sizeof(JSONValue));
  while (tokens->items[*index].type != TOKEN_RCURLY) {
    const char *key = tokens->items[*index].value;
    // skip key
    (*index)++;

    (*index)++;
    // skip colon
    JSONValue *val = parse_value(tokens, index);

    if (tokens->items[*index].type == TOKEN_COMA) {
      (*index)++;
    };
  };

  // skip TOKEN_RCURLY
  (*index)++;

  return obj_node;
}

JSONValue *parse_value(TokenArray *tokens, size_t *index) {
  if (*index >= tokens->size)
    return NULL;

  Token *current = &tokens->items[*index];
  JSONValue *val = malloc(sizeof(JSONValue));
  if (val == NULL)
    return NULL;

  switch (current->type) {
  case TOKEN_LCURLY:
    free(val);
    val = NULL;
    return parse_object(tokens, index);

  case TOKEN_STRING:
    val->type = JSON_STRING;
    val->data.str = strdup(current->value);
    (*index)++;
    return val;

  case TOKEN_NUMBER:
    val->type = JSON_NUMBER;
    val->data.boolean = (strcmp(current->value, "true") == 0);
    (*index)++;
    return val;
  case TOKEN_NULL:
    val->type = JSON_NULL;
    (*index)++;
    return val;

  default:
    free(val);
    val = NULL;
    return NULL;
  }
}
