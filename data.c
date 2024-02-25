#include "lisp.h"
#include <stdlib.h>
#include <string.h>

atom bl_pair(atom head, atom tail) {
  atom p;

  p.type = PAIR;
  p.value.pair = malloc(sizeof(struct pair));

  head(p) = head;
  tail(p) = tail;

  return p;
}

atom bl_int(long x) {
  atom a;

  a.type = INTEGER;
  a.value.integer = x;

  return a;
}

static atom sym_table = {NIL};

atom bl_sym(const char *s) {
  atom a, p;

  p = sym_table;
  while (p.type != NIL) {
    a = head(p);
    if (strcmp(a.value.symbol, s) == 0) {
      return a;
    }
    p = tail(p);
  }
  a.type = SYMBOL;
  a.value.symbol = strdup(s);
  sym_table = bl_pair(a, sym_table);

  return a;
}