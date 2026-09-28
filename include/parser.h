#ifndef PARSER_H
#define PARSER_H
#include "datatypes.h"

JSONValue *parse_object(TokenArray *tokens, size_t *index);
JSONValue *parse_value(TokenArray *tokens, size_t *index);

#endif
