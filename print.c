#include "lisp.h"
#include <stdio.h>

void bl_print(atom_type atom) {
  switch (atom.type) {
  case NIL:
    printf("()");
    break;
  case PAIR:
    putchar('(');
    bl_print(head_macro(atom));
    atom = tail_macro(atom);
    while (atom.type != NIL) {
      if (atom.type == PAIR) {
        putchar(' ');
        bl_print(head_macro(atom));
        atom = tail_macro(atom);
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