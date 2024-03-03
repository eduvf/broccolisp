#include "lisp.h"
#include <stdlib.h>
#include <string.h>

atom_type bl_pair(atom_type head, atom_type tail) {
  atom_type p;

  p.type = PAIR;
  p.value.pair = malloc(sizeof(struct pair));

  head_macro(p) = head;
  tail_macro(p) = tail;

  return p;
}

atom_type bl_int(long x) {
  atom_type a;

  a.type = INTEGER;
  a.value.integer = x;

  return a;
}

static atom_type sym_table = {NIL};

atom_type bl_sym(const char *s) {
  atom_type a, p;

  p = sym_table;
  while (p.type != NIL) {
    a = head_macro(p);
    if (strcmp(a.value.symbol, s) == 0) {
      return a;
    }
    p = tail_macro(p);
  }
  a.type = SYMBOL;
  a.value.symbol = strdup(s);
  sym_table = bl_pair(a, sym_table);

  return a;
}

atom_type bl_env(atom_type outer) {
  // create empty environment
  return bl_pair(outer, nil);
}

int bl_get(atom_type env, atom_type sym, atom_type *result) {
  atom_type outer = head_macro(env);
  atom_type current = tail_macro(env);

  while (current.type != NIL) {
    atom_type binding = head_macro(current);
    if (head_macro(binding).value.symbol == sym.value.symbol) {
      *result = tail_macro(binding);
      return NO_ERR;
    }
    current = tail_macro(current);
  }

  if (outer.type == NIL) {
    return UNDEFINED_SYMBOL_ERR;
  }
  return bl_get(outer, sym, result);
}

int bl_set(atom_type env, atom_type sym, atom_type value) {
  atom_type current = tail_macro(env);
  atom_type binding = nil;

  while (current.type != NIL) {
    binding = head_macro(current);
    if (head_macro(binding).value.symbol == sym.value.symbol) {
      tail_macro(binding) = value;
      return NO_ERR;
    }
    current = tail_macro(current);
  }

  binding = bl_pair(sym, value);
  tail_macro(env) = bl_pair(binding, tail_macro(env));

  return NO_ERR;
}