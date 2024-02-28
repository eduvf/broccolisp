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