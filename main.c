// #include "raylib.h"
// #include <stdbool.h>
#include "lisp.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  char *input;
  type_atom env = fn_make_env(nil);

  fn_set_into_env(env, fn_make_symbol("car"), fn_make_function(fn_lisp_car));
  fn_set_into_env(env, fn_make_symbol("cdr"), fn_make_function(fn_lisp_cdr));
  fn_set_into_env(env, fn_make_symbol("cons"), fn_make_function(fn_lisp_cons));

  while ((input = readline("? ")) != NULL) {
    const char *p = input;
    type_error error;
    type_atom expr, result;

    error = fn_read(p, &p, &expr);

    if (!error) {
      error = fn_eval(expr, env, &result);
    }

    switch (error) {
    case NO_ERROR:
      fn_print(result);
      puts("");
      break;
    case SYNTAX_ERROR:
      puts("(!) Syntax error");
      break;
    case UNDEFINED_SYMBOL_ERROR:
      puts("(!) Undefined symbol error");
      break;
    case EVAL_NO_BINDING_ERROR:
      puts("(!) Can't evaluate symbol without binding");
      break;
    case ARGUMENT_NUMBER_ERROR:
      puts("(!) Arguments number error");
      break;
    case TYPE_ERROR:
      puts("(!) Unexpected type error");
      break;
    case QUIT_ERROR:
      free(input);
      return 0;
    }

    free(input);
  }

  return 0;
}

/*
char input[256] = "\0";
int input_len = 0;

void check_input() {
  int key = GetCharPressed();

  if (key > 0) {
    if ((key >= 32) && (key <= 125) && (input_len < 255)) {
      input[input_len++] = (char)key;
      input[input_len] = '\0';
    }
  }
}

int main() {
  const int SCREEN_WIDTH = 630;
  const int SCREEN_HEIGHT = 360;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "broccolisp");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    check_input();

    BeginDrawing();

    DrawText(input, 20, 20, 20, WHITE);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
*/