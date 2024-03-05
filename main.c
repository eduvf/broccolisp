// #include "raylib.h"
// #include <stdbool.h>
#include "lisp.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  char *input;

  while ((input = readline("? ")) != NULL) {
    const char *p = input;
    type_error error;
    type_atom expr;

    error = fn_read(p, &p, &expr);

    switch (error) {
    case NO_ERROR:
      fn_print(expr);
      puts("");
      break;
    case SYNTAX_ERROR:
      puts("(!) Syntax error");
      break;
    case UNDEFINED_SYMBOL_ERROR:
      puts("(!) Undefined symbol error");
      break;
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