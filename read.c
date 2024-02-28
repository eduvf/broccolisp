#include "lisp.h"
#include <string.h>

int bl_lex(const char *s, const char **from, const char **to) {
  const char *whitespace = " \t\n";
  const char *delimiter = "() \t\n";

  s += strspn(s, whitespace);

  if (s[0] == '\0') {
    *from = NULL;
    *to = NULL;
    return SYNTAX_ERR;
  }

  *from = s;

  if (s[0] == '(' || s[0] == ')') {
    *to = s + 1;
  } else {
    *to = s + strcspn(s, delimiter);
  }

  return NO_ERR;
}