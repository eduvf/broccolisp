#ifndef LISP
#define LISP

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

#endif