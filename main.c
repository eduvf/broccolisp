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
    error_type err;
    atom_type expr;

    err = bl_read(p, &p, &expr);

    switch (err) {
    case NO_ERR:
      bl_print(expr);
      puts("");
      break;
    case SYNTAX_ERR:
      puts("(!) Syntax error");
      break;
    case UNDEFINED_SYMBOL_ERR:
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