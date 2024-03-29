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

void checkCollision(std::map<int, int *> *mp, int x, int y) {
  std::map<int, int *>::iterator it;
  for (it = mp->begin(); it != mp->end(); ++it) {
    if ((it->second)[0] == x && (it->second)[1] == y) {
      CloseWindow();
    }
  }
}

int *snakeQueue(std::map<int, int *> *mp, int spdx, int spdy, int count,
                int size, bool hasGrown) {
  int oldX = (*mp)[count - 1][0] + spdx;
  int oldY = (*mp)[count - 1][1] + spdy;
  checkCollision(&*mp, oldX, oldY);
  int *arr = new int[2]{oldX, oldY};
  (*mp)[count] = arr;
  if (!hasGrown) {
    mp->erase(count - size);
  }
  return new int[2]{oldX, oldY};
}

int main() {
  InitWindow(SCR_W, SCR_H, "testWindow");

  std::map<int, int *> m;
  m[0] = new int[2]{250, 250};

  int size = 20;
  int count = 1;

  int lastKey;
  int xspd = 0;
  int yspd = 25;

  int timeCount = 0;
  int *arr;
  arr[0] = 0;
  arr[1] = 1;

  SetTargetFPS(60);
  if (IsWindowReady()) {

    while (!WindowShouldClose()) {
      timeCount++;
      BeginDrawing();
      ClearBackground(BLACK);

      std::string fps =
          std::to_string(std::round((1000 / GetFrameTime() / 1000)));
      DrawText(fps.c_str(), 0, 0, 20, Color(WHITE));
      DrawText(std::to_string(arr[0]).c_str(), 200, 0, 20, Color(WHITE));
      DrawText(std::to_string(arr[1]).c_str(), 300, 0, 20, Color(WHITE));

      checkKeys(&lastKey, &xspd, &yspd);

      if (timeCount >= 6) {
        arr = snakeQueue(&m, xspd, yspd, count, size, (size != m.size()));
        count++;
        timeCount = 0;
      }
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
