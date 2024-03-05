#ifndef LISP
#define LISP

typedef enum { NO_ERROR, SYNTAX_ERROR, UNDEFINED_SYMBOL_ERROR } type_error;

struct struct_atom {
  enum {
    NIL,
    PAIR,
    SYMBOL,
    INTEGER,
  } type;
  union {
    struct struct_pair *pair;
    const char *symbol;
    long integer;
  } value;
};

struct struct_pair {
  struct struct_atom head;
  struct struct_atom tail;
};

typedef struct struct_atom type_atom;

static const type_atom nil = {};

#define head(p) ((p).value.pair->head)
#define tail(p) ((p).value.pair->tail)

type_atom fn_make_pair(type_atom head, type_atom tail);
type_atom fn_make_int(long integer);
type_atom fn_make_symbol(const char *string);
type_atom fn_make_env(type_atom outer);

int fn_get_from_env(type_atom env, type_atom symbol, type_atom *result);
int fn_set_into_env(type_atom env, type_atom symbol, type_atom value);

int fn_lex(const char *string, const char **start, const char **end);
int fn_parse_atom(const char *start, const char *end, type_atom *result);
int fn_parse_list(const char *start, const char **end, type_atom *result);
int fn_read(const char *input, const char **end, type_atom *result);

void fn_print(type_atom atom);

#endif