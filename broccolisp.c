#include "raylib.h"
#include <stdbool.h>

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