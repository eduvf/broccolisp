#include "lisp.h"

int fn_get_from_env(type_atom env, type_atom symbol, type_atom *result) {
  type_atom outer = head(env);
  type_atom current = tail(env);

  // search for symbol in current env
  while (current.type != NIL) {
    type_atom binding = head(current);
    if (head(binding).value.symbol == symbol.value.symbol) {
      *result = tail(binding);
      return NO_ERROR;
    }
    current = tail(current);
  }

  if (outer.type == NIL) {
    return UNDEFINED_SYMBOL_ERROR;
  }
  // search recursively into outer env
  return fn_get_from_env(outer, symbol, result);
}

int fn_set_into_env(type_atom env, type_atom symbol, type_atom value) {
  type_atom current = tail(env);
  type_atom binding = nil;

  // search for symbol
  while (current.type != NIL) {
    binding = head(current);
    if (head(binding).value.symbol == symbol.value.symbol) {
      tail(binding) = value;
      return NO_ERROR;
    }
    current = tail(current);
  }

  // define the value in current env
  binding = fn_make_pair(symbol, value);
  tail(env) = fn_make_pair(binding, tail(env));

  return NO_ERROR;
}