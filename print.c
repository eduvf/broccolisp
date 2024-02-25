#include "lisp.h"
#include <stdio.h>

void bl_print(atom atom) {
  switch (atom.type) {
  case NIL:
    printf("()");
    break;
  case PAIR:
    putchar('(');
    bl_print(head(atom));
    atom = tail(atom);
    while (atom.type != NIL) {
      if (atom.type == PAIR) {
        putchar(' ');
        bl_print(head(atom));
        atom = tail(atom);
      } else {
        printf(" . ");
        bl_print(atom);
        break;
      }
    }
    putchar(')');
    break;
  case SYMBOL:
    printf("%s", atom.value.symbol);
    break;
  case INTEGER:
    printf("%ld", atom.value.integer);
    break;
  }
}