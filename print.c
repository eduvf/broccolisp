#include "lisp.h"
#include <stdio.h>

void fn_print(type_atom atom) {
  switch (atom.type) {
  case NIL:
    printf("()");
    break;
  case PAIR:
    putchar('(');
    // print recursively the contents of head and tail
    fn_print(head(atom));
    atom = tail(atom);
    while (atom.type != NIL) {
      // if the tail is not a pair,
      // separate head and tail with a dot (head . tail)
      if (atom.type == PAIR) {
        putchar(' ');
        fn_print(head(atom));
        atom = tail(atom);
      } else {
        printf(" . ");
        fn_print(atom);
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