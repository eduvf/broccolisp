#include "lisp.h"
#include <stdlib.h>
#include <string.h>

type_atom fn_make_pair(type_atom head, type_atom tail) {
  type_atom pair;

  pair.type = PAIR;
  pair.value.pair = malloc(sizeof(struct struct_pair));

  head(pair) = head;
  tail(pair) = tail;

  return pair;
}

type_atom fn_make_int(long integer) {
  type_atom atom;

  atom.type = INTEGER;
  atom.value.integer = integer;

  return atom;
}

static type_atom symbol_table = {NIL};

type_atom fn_make_symbol(const char *string) {
  type_atom atom, pair;

  pair = symbol_table;
  while (pair.type != NIL) {
    atom = head(pair);
    if (strcmp(atom.value.symbol, string) == 0) {
      return atom;
    }
    pair = tail(pair);
  }
  atom.type = SYMBOL;
  atom.value.symbol = strdup(string);
  symbol_table = fn_make_pair(atom, symbol_table);

  return atom;
}

type_atom fn_make_env(type_atom outer) {
  // create empty environment
  return fn_make_pair(outer, nil);
}

int fn_get_from_env(type_atom env, type_atom symbol, type_atom *result) {
  type_atom outer = head(env);
  type_atom current = tail(env);

  while (current.type != NIL) {
    type_atom binding = head(current);
    if (head(binding).value.symbol == symbol.value.symbol) {
      *result = tail(binding);
      return NO_ERROR;
    }
    current = tail(current);
  }

  if (outer.type == NIL) {
    return UNDEFINED_SYMBOL_ERROR;
  }
  return fn_get_from_env(outer, symbol, result);
}

int fn_set_into_env(type_atom env, type_atom symbol, type_atom value) {
  type_atom current = tail(env);
  type_atom binding = nil;

  while (current.type != NIL) {
    binding = head(current);
    if (head(binding).value.symbol == symbol.value.symbol) {
      tail(binding) = value;
      return NO_ERROR;
    }
    current = tail(current);
  }

  binding = fn_make_pair(symbol, value);
  tail(env) = fn_make_pair(binding, tail(env));

  return NO_ERROR;
}