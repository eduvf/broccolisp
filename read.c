#include "lisp.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int fn_lex(const char *string, const char **start, const char **end) {
  const char *whitespace = " \t\n";
  const char *delimiter = "() \t\n";

  // consume whitespace
  string += strspn(string, whitespace);

  // check for empty string
  if (string[0] == '\0') {
    *start = NULL;
    *end = NULL;
    return SYNTAX_ERROR;
  }

  // adjust start pointer
  *start = string;

  if (string[0] == '(' || string[0] == ')') {
    // capture parentheses
    *end = string + 1;
  } else {
    // capture symbol or number
    *end = string + strcspn(string, delimiter);
  }

  return NO_ERROR;
}

int fn_parse_atom(const char *start, const char *end, type_atom *result) {
  char *buffer;
  char *pair;

  // check for number
  long value = strtol(start, &pair, 10);
  if (pair == end) {
    result->type = INTEGER;
    result->value.integer = value;
    return NO_ERROR;
  }

  // calculate buffer size based on pointers
  buffer = malloc(end - start + 1);
  pair = buffer;
  while (start != end) {
    *pair = tolower(*start);
    start++;
    pair++;
  }
  // add null char to the end of the symbol
  *pair = '\0';

  // check for "nil", otherwise it's a symbol
  if (strcmp(buffer, "nil") == 0) {
    *result = nil;
  } else {
    *result = fn_make_symbol(buffer);
  }

  free(buffer);
  return NO_ERROR;
}

int fn_parse_list(const char *start, const char **end, type_atom *result) {
  type_atom pair;

  *end = start;
  pair = nil;
  *result = nil;

  for (;;) {
    const char *token;
    type_atom atom;
    type_error error;

    // lex a single token
    error = fn_lex(*end, &token, end);
    if (error) {
      return error;
    }

    // closing paren ends the list
    if (token[0] == ')') {
      return NO_ERROR;
    }

    // check if it's an explicit pair (x . y)
    if (token[0] == '.' && *end - token == 1) {
      if (pair.type == NIL) {
        return SYNTAX_ERROR;
      }

      // read the tail of the pair
      error = fn_read(*end, end, &atom);
      if (error) {
        return error;
      }

      tail(pair) = atom;

      // check that the pair ends
      error = fn_lex(*end, &token, end);
      if (!error && token[0] != ')') {
        error = SYNTAX_ERROR;
      }

      return error;
    }

    // check if it's an atom
    error = fn_read(token, end, &atom);
    if (error) {
      return error;
    }

    if (pair.type == NIL) {
      // end list
      *result = fn_make_pair(atom, nil);
      pair = *result;
    } else {
      // add atom to continue list
      tail(pair) = fn_make_pair(atom, nil);
      pair = tail(pair);
    }
  }
}

int fn_read(const char *input, const char **end, type_atom *result) {
  const char *token;
  type_error error;

  error = fn_lex(input, &token, end);
  if (error) {
    return error;
  }

  if (token[0] == '(') {
    return fn_parse_list(*end, end, result);
  } else if (token[0] == ')') {
    return SYNTAX_ERROR;
  } else {
    return fn_parse_atom(token, *end, result);
  }
}