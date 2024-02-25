// #include "raylib.h"
// #include <stdbool.h>
#include "data.c"
#include "print.c"
#include <stdio.h>

int main() {
  char c;

  bl_print(bl_int(42));
  putchar('\n');
  bl_print(bl_pair(bl_int(1), bl_pair(bl_int(2), bl_pair(bl_int(3), nil))));
  putchar('\n');
  bl_print(bl_pair(bl_sym("p"), bl_pair(bl_sym("q"), bl_sym("r"))));
  putchar('\n');

  printf("?");
  scanf("%c", &c);

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