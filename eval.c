#include "lisp.h"
#include <string.h>

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

int fn_check_if_proper_list(type_atom expr) {
  // traverse the list and return 0 if any of the tails
  // is not a pair or nil (end of the list)
  while (expr.type != NIL) {
    if (expr.type != PAIR) {
      return 0;
    }
    expr = tail(expr);
  }
  return 1;
}

int fn_apply(type_atom function, type_atom args, type_atom *result) {
  // check for a built-in function
  if (function.type == FUNCTION) {
    return (*function.value.function)(args, result);
  }
  return TYPE_ERROR;
}

int fn_eval(type_atom expr, type_atom env, type_atom *result) {
  type_atom operation;
  type_atom arguments;
  type_atom pair;
  type_error error;

  if (expr.type == SYMBOL) {
    // evaluate the symbol into result and return error
    return fn_get_from_env(env, expr, result);
  }

  if (expr.type != PAIR) {
    // is integer
    *result = expr;
    return NO_ERROR;
  }

  if (!fn_check_if_proper_list(expr)) {
    // has to be a proper list to evaluate
    return SYNTAX_ERROR;
  }

  operation = head(expr);
  arguments = tail(expr);

  if (operation.type == SYMBOL) {
    // check for special forms

    if (strcmp(operation.value.symbol, "quote") == 0) {
      // quote requires a single argument
      if (arguments.type == NIL || tail(arguments).type != NIL) {
        return ARGUMENT_NUMBER_ERROR;
      }
      // put the argument into result without evaluation
      *result = head(arguments);
      return NO_ERROR;
    }

    if (strcmp(operation.value.symbol, "define") == 0) {
      // define requires two arguments
      if (arguments.type == NIL || tail(arguments).type == NIL ||
          tail(tail(arguments)).type != NIL) {
        return ARGUMENT_NUMBER_ERROR;
      }

      // first argument has to be a symbol
      type_atom symbol = head(arguments);
      if (symbol.type != SYMBOL) {
        return TYPE_ERROR;
      }

      // second argument is evaluated
      type_atom value;
      error = fn_eval(head(tail(arguments)), env, &value);
      if (error) {
        return error;
      }

      *result = symbol;
      return fn_set_into_env(env, symbol, value);
    }

    if (strcmp(operation.value.symbol, "quit") == 0) {
      // quit the program
      return QUIT_ERROR;
    }
  }

  // check for a function
  // try to override the operation with its value
  error = fn_eval(operation, env, &operation);
  if (error) {
    return error;
  }

  // copy and iterate the argument list, while evaluating it
  arguments = fn_list_shallow_copy(arguments);
  pair = arguments;
  while (pair.type != NIL) {
    error = fn_eval(head(pair), env, &head(pair));
    if (error) {
      return error;
    }
    pair = tail(pair);
  }

  return fn_apply(operation, arguments, result);
}