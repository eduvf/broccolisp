#ifndef LISP
#define LISP

typedef enum { NO_ERR, SYNTAX_ERR } error_type;

struct atom {
  enum {
    NIL,
    PAIR,
    SYMBOL,
    INTEGER,
  } type;
  union {
    struct pair *pair;
    const char *symbol;
    long integer;
  } value;
};

struct pair {
  struct atom head;
  struct atom tail;
};

typedef struct atom atom_type;

static const atom_type nil = {};

#define head_macro(p) ((p).value.pair->head)
#define tail_macro(p) ((p).value.pair->tail)

atom_type bl_pair(atom_type head, atom_type tail);
atom_type bl_int(long x);
atom_type bl_sym(const char *s);

int bl_lex(const char *s, const char **from, const char **to);

void bl_print(atom_type atom);

#endif