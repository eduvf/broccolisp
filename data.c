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
  type_atom atom;
  type_atom pair;

  // check if the symbol already exists,
  // and return if so
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

type_atom fn_make_function(type_function function) {
  type_atom atom;

  atom.type = FUNCTION;
  atom.value.function = function;

  return atom;
}

type_atom fn_make_env(type_atom outer) {
  // create empty environment
  return fn_make_pair(outer, nil);
}

type_atom fn_list_shallow_copy(type_atom list) {
  type_atom atom;
  type_atom pair;

  // check for an empty list (no need to copy)
  if (list.type == NIL) {
    return nil;
  }

  atom = fn_make_pair(head(list), nil);
  pair = atom;
  list = tail(list);

  // go through all atoms in list and copy them into pair
  while (list.type != NIL) {
    tail(pair) = fn_make_pair(head(list), nil);
    pair = tail(pair);
    list = tail(list);
  }

  return atom;
}