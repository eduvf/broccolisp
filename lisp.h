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

typedef struct atom atom;

static const atom nil = {};

#define head(p) ((p).value.pair->head)
#define tail(p) ((p).value.pair->tail)

#endif