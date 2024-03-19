#include "lisp.h"

int fn_lisp_car(type_atom args, type_atom *result) {
  // check argument number (has to be == 1)
  if (args.type == NIL || tail(args).type != NIL) {
    return ARGUMENT_NUMBER_ERROR;
  }

  if (head(args).type == NIL) {
    // is nil (nothing to return)
    *result = nil;
  } else if (head(args).type != PAIR) {
    // is not a pair (cannot get the CAR of an atom)
    return TYPE_ERROR;
  } else {
    // is a pair, get the CAR (== HEAD)
    *result = head(head(args));
  }

  return NO_ERROR;
}

int fn_lisp_cdr(type_atom args, type_atom *result) {
  // check argument number (has to be == 1)
  if (args.type == NIL || tail(args).type != NIL) {
    return ARGUMENT_NUMBER_ERROR;
  }

  if (head(args).type == NIL) {
    // is nil (nothing to return)
    *result = nil;
  } else if (head(args).type != PAIR) {
    // is not a pair (cannot get the CAR of an atom)
    return TYPE_ERROR;
  } else {
    // is a pair, get the CDR (== TAIL)
    *result = tail(head(args));
  }

  return NO_ERROR;
}

int fn_lisp_cons(type_atom args, type_atom *result) {
  // check argument number (has to be == 2)
  if (args.type == NIL || tail(args).type == NIL ||
      tail(tail(args)).type != NIL) {
    return ARGUMENT_NUMBER_ERROR;
  }

  *result = fn_make_pair(head(args), head(tail(args)));

  return NO_ERROR;
}