#include "raylib.h"

int main() {
  InitWindow(500, 500, "broccolisp");

  while (!WindowShouldClose()) {
    BeginDrawing();

    DrawText("Hi!", 200, 200, 20, RED);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}