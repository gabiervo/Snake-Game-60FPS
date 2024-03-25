#include "/usr/local/Cellar/raylib/5.0/include/raylib.h"
#include <cmath>
#include <map>
#include <string>
#include <utility>
#include <vector>

#define SCR_W 800
#define SCR_H 500

class snake {
public:
  int index;
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

void spawnSnake(std::map<int, int *> *mp) {
  snake snk(mp->size() - 1);

  int newX = (*mp)[snk.index - 1][0];
  int newY = (*mp)[snk.index - 1][1];

  int *newArr = new int[2];
  newArr[0] = newX;
  newArr[1] = newY;

  std::pair<int, int *> pair = std::make_pair(snk.index, newArr);
  mp->insert(pair);

  delete[] newArr;
}

int main() {
  InitWindow(SCR_W, SCR_H, "testWindow");

  std::map<int, int *> m;

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
        spawnSnake(&m);
      }
      // loop to update position values
      for (int i = snakeList.size() - 1; i > 1; i--) {
        snake *obj = &snakeList[i];
      }

      // need to add headSnake spawn
      checkKeys(&lastKey, &xspd, &yspd);
      // loop to draw snakes
      for (int i = 0; i < snakeList.size(); i++) {
        snake *obj = &snakeList[i];
      }

      EndDrawing();
    }
  }
  CloseWindow();
  return 0;
}
