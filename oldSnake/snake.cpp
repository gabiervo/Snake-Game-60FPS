#include "/usr/local/Cellar/raylib/5.0/include/raylib.h"
#include <cmath>
#include <string>
#include <vector>

#define SCR_W 800
#define SCR_H 500

class snake {
public:
  int index;
  int width = 25;
  int height = 25;
  snake(int in) { index = in; }
};

void checkKeys(int *k, int *xspd, int *yspd) {
  int key = -1;
  if (IsKeyDown(KEY_RIGHT) && *k != KEY_LEFT) {
    *xspd = 2;
    *yspd = 0;
    *k = KEY_RIGHT;
  }
  if (IsKeyDown(KEY_LEFT) and *k != KEY_RIGHT) {
    *xspd = -2;
    *yspd = 0;
    *k = KEY_LEFT;
  }
  if (IsKeyDown(KEY_UP) && *k != KEY_DOWN) {
    *yspd = -2;
    *xspd = 0;
    *k = KEY_UP;
  }
  if (IsKeyDown(KEY_DOWN) && *k != KEY_UP) {
    *yspd = 2;
    *xspd = 0;
    *k = KEY_DOWN;
  }
}

void spawnSnake(std::vector<int> *xList, std::vector<int> *yList,
                std::vector<snake> *snkList, int s) {
  snake snk(snkList->size() - 1);

  int newX = (*xList)[snk.index - 1];
  xList->push_back(newX);

  int newY = (*yList)[snk.index - 1];
  yList->push_back(newY);

  snkList->push_back(snk);
}

int main() {
  InitWindow(SCR_W, SCR_H, "testWindow");
  std::vector<int> sX = {200};
  std::vector<int> sY = {250};
  snake headSnake(0);
  std::vector<snake> snakeList = {headSnake};

  int size = 10;

  int lastKey;
  int xspd = 0;
  int yspd = -2;

  SetTargetFPS(60);
  if (IsWindowReady()) {

    while (!WindowShouldClose()) {

      BeginDrawing();
      ClearBackground(BLACK);

      std::string fps =
          std::to_string(std::round((1000 / GetFrameTime() / 1000)));
      DrawText(fps.c_str(), 0, 0, 20, Color(WHITE));

      while (size != snakeList.size()) {
        spawnSnake(&sX, &sY, &snakeList, size);
      }

      for (int i = snakeList.size() - 1; i > 1; i--) {
        snake *obj = &snakeList[i];

        sX[obj->index] = sX[obj->index - 1];
        sY[obj->index] = sY[obj->index - 1];
      }

      checkKeys(&lastKey, &xspd, &yspd);

      sX[0] += xspd;
      sY[0] += yspd;
      for (int i = 0; i < snakeList.size(); i++) {
        snake *obj = &snakeList[i];
        DrawRectangle(sX[obj->index], sY[obj->index], obj->width, obj->height,
                      Color(WHITE));
      }

      EndDrawing();
    }
  }
  CloseWindow();
  return 0;
}
