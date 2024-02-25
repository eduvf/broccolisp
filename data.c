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

atom bl_sym(const char *s) {
  atom a;

  a.type = SYMBOL;
  a.value.symbol = strdup(s);

  return a;
}