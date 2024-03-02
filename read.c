#include "lisp.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int bl_lex(const char *s, const char **from, const char **to) {
  const char *whitespace = " \t\n";
  const char *delimiter = "() \t\n";

  s += strspn(s, whitespace);

  if (s[0] == '\0') {
    *from = NULL;
    *to = NULL;
    return SYNTAX_ERR;
  }

  *from = s;

  if (s[0] == '(' || s[0] == ')') {
    *to = s + 1;
  } else {
    *to = s + strcspn(s, delimiter);
  }

  return NO_ERR;
}

int bl_parse_atom(const char *from, const char *to, atom_type *result) {
  char *buffer;
  char *p;

  long value = strtol(from, &p, 10);
  if (p == to) {
    result->type = INTEGER;
    result->value.integer = value;
    return NO_ERR;
  }

  buffer = malloc(to - from + 1);
  p = buffer;
  while (from != to) {
    // FIX
    *p++ = tolower(*from), ++from;
  }
  *p = '\0';

  if (strcmp(buffer, "nil") == 0) {
    *result = nil;
  } else {
    *result = bl_sym(buffer);
  }

  free(buffer);
  return NO_ERR;
}

int bl_parse_list(const char *from, const char **to, atom_type *result) {
  atom_type p;

  *to = from;
  p = nil;
  *result = nil;

  for (;;) {
    const char *token;
    atom_type atom;
    error_type err;

    err = bl_lex(*to, &token, to);
    if (err) {
      return err;
    }

    if (token[0] == ')') {
      return SYNTAX_ERR;
    }

    if (token[0] == '.' && *to - token == 1) {
      if (p.type == NIL) {
        return SYNTAX_ERR;
      }

      err = bl_read(*to, to, &atom);
      if (err) {
        return err;
      }

      tail_macro(p) = atom;

      err = bl_lex(*to, &token, to);
      if (!err && token[0] != ')') {
        err = SYNTAX_ERR;
      }

      return err;
    }

    err = bl_read(token, to, &atom);
    if (err) {
      return err;
    }

    if (p.type == NIL) {
      *result = bl_pair(atom, nil);
      p = *result;
    } else {
      tail_macro(p) = bl_pair(atom, nil);
      p = tail_macro(p);
    }
  }
}

int bl_read(const char *input, const char **to, atom_type *result) {
  const char *token;
  error_type err;

  err = bl_lex(input, &token, to);
  if (err) {
    return err;
  }

  if (token[0] == '(') {
    return bl_parse_list(*to, to, result);
  } else if (token[0] == ')') {
    return SYNTAX_ERR;
  } else {
    return bl_parse_atom(token, *to, result);
  }
}