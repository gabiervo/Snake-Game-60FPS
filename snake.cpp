#include "/usr/local/Cellar/raylib/5.0/include/raylib.h"
#include <cmath>
#include <map>
#include <string>
#include <utility>

#define SCR_W 800
#define SCR_H 500

void checkKeys(int *k, int *xspd, int *yspd) {
  int key = -1;
  if (IsKeyDown(KEY_RIGHT) && *k != KEY_LEFT) {
    *xspd = 25;
    *yspd = 0;
    *k = KEY_RIGHT;
  }
  if (IsKeyDown(KEY_LEFT) and *k != KEY_RIGHT) {
    *xspd = -25;
    *yspd = 0;
    *k = KEY_LEFT;
  }
  if (IsKeyDown(KEY_UP) && *k != KEY_DOWN) {
    *yspd = -25;
    *xspd = 0;
    *k = KEY_UP;
  }
  if (IsKeyDown(KEY_DOWN) && *k != KEY_UP) {
    *yspd = 25;
    *xspd = 0;
    *k = KEY_DOWN;
  }
}

void snakeQueue(std::map<int, int *> *mp, int spdx, int spdy, int count,
                int size) {
  int oldX = (*mp)[count - 1][0] + spdx;
  int oldY = (*mp)[count - 1][1] + spdy;
  int *arr = new int[2]{oldX, oldY};
  (*mp)[count] = arr;
  mp->erase(count - size);
}

int main() {
  InitWindow(SCR_W, SCR_H, "testWindow");

  std::map<int, int *> m;
  m[0] = new int[2]{250, 20};

  int size = 1;
  int count = 1;

  int lastKey;
  int xspd = 0;
  int yspd = 25;

  SetTargetFPS(15);
  if (IsWindowReady()) {

    while (!WindowShouldClose()) {

      BeginDrawing();
      ClearBackground(BLACK);

      std::string fps =
          std::to_string(std::round((1000 / GetFrameTime() / 1000)));
      DrawText(fps.c_str(), 0, 0, 20, Color(WHITE));

      checkKeys(&lastKey, &xspd, &yspd);
      snakeQueue(&m, xspd, yspd, count, size);
      count++;
      // loop to draw snakes
      std::map<int, int *>::iterator it;
      it = m.begin();

      for (it = it++; it != m.end(); ++it) {
        DrawRectangle((it->second)[0], (it->second)[1], 25, 25, Color(WHITE));
      }
      EndDrawing();
    }
  }
  CloseWindow();
  return 0;
}
