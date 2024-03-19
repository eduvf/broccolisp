#ifndef LISP
#define LISP

typedef enum {
  NO_ERROR,
  SYNTAX_ERROR,
  UNDEFINED_SYMBOL_ERROR,
  EVAL_NO_BINDING_ERROR,
  ARGUMENT_NUMBER_ERROR,
  TYPE_ERROR,
  QUIT_ERROR
} type_error;

struct struct_atom;

typedef struct struct_atom type_atom;
typedef int (*type_function)(type_atom arguments, type_atom *result);

struct struct_atom {
  enum {
    NIL,
    PAIR,
    SYMBOL,
    INTEGER,
    FUNCTION,
  } type;
  union {
    struct struct_pair *pair;
    const char *symbol;
    long integer;
    type_function function;
  } value;
};

struct struct_pair {
  struct struct_atom head;
  struct struct_atom tail;
};

static const type_atom nil = {};

#define head(p) ((p).value.pair->head)
#define tail(p) ((p).value.pair->tail)

type_atom fn_make_pair(type_atom head, type_atom tail);
type_atom fn_make_int(long integer);
type_atom fn_make_symbol(const char *string);
type_atom fn_make_env(type_atom outer);

type_atom fn_list_shallow_copy(type_atom list);

int fn_lex(const char *string, const char **start, const char **end);
int fn_parse_atom(const char *start, const char *end, type_atom *result);
int fn_parse_list(const char *start, const char **end, type_atom *result);
int fn_read(const char *input, const char **end, type_atom *result);

int fn_get_from_env(type_atom env, type_atom symbol, type_atom *result);
int fn_set_into_env(type_atom env, type_atom symbol, type_atom value);
int fn_check_if_proper_list(type_atom expr);
int fn_apply(type_atom function, type_atom args, type_atom *result);
int fn_eval(type_atom expr, type_atom env, type_atom *result);

void fn_print(type_atom atom);

#endif