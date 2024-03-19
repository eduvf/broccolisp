#include "lisp.h"

int fn_lisp_car(type_atom args, type_atom *result) {
  // check argument number (has to be == 1)
  if (args.type == NIL || tail(args).type != NIL) {
    return ARGUMENT_NUMBER_ERROR;
  }
}

int fn_lisp_cdr(type_atom args, type_atom *result) {
  // check argument number (has to be == 1)
  if (args.type == NIL || tail(args).type != NIL) {
    return ARGUMENT_NUMBER_ERROR;
  }
}

int fn_lisp_cons(type_atom args, type_atom *result) {
  // check argument number (has to be == 2)
  if (args.type == NIL || tail(args).type == NIL ||
      tail(tail(args)).type != NIL) {
    return ARGUMENT_NUMBER_ERROR;
  }
}