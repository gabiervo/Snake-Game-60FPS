#include "/usr/local/Cellar/raylib/5.0/include/raylib.h"
#include <cmath>
#include <map>
#include <string>
#include <utility>
#include <vector>

#define SCR_W 800
#define SCR_H 500

void checkKeys(int *k, std::vector<int> *inB) {
  if (IsKeyDown(KEY_RIGHT) && *k != KEY_LEFT) {
    if ((*inB)[inB->size() - 1] != *k && inB->size() < 2) {
      inB->push_back(*k);
    }
    *k = KEY_RIGHT;
  }
  if (IsKeyDown(KEY_LEFT) and *k != KEY_RIGHT) {
    if ((*inB)[inB->size() - 1] != *k && inB->size() < 2) {
      inB->push_back(*k);
    }
    *k = KEY_LEFT;
  }
  if (IsKeyDown(KEY_UP) && *k != KEY_DOWN) {
    if ((*inB)[inB->size() - 1] != *k && inB->size() < 2) {
      inB->push_back(*k);
    }
    *k = KEY_UP;
  }
  if (IsKeyDown(KEY_DOWN) && *k != KEY_UP) {
    if ((*inB)[inB->size() - 1] != *k && inB->size() < 2) {
      inB->push_back(*k);
    }
    *k = KEY_DOWN;
  }
}

void executeInput(std::vector<int> *buffer, int *xspd, int *yspd) {
  if (buffer->size() > 0) {
    if ((*buffer)[0] == KEY_DOWN && *yspd != -20) {
      *xspd = 0;
      *yspd = 20;
    }
    if ((*buffer)[0] == KEY_UP && *yspd != 20) {
      *xspd = 0;
      *yspd = -20;
    }
    if ((*buffer)[0] == KEY_RIGHT && *xspd != -20) {
      *xspd = 20;
      *yspd = 0;
    }
    if ((*buffer)[0] == KEY_LEFT && *xspd != 20) {
      *xspd = -20;
      *yspd = 0;
    }
    *buffer->erase(buffer->begin());
  }
}

bool shouldPlay = true;

void checkCollision(std::map<int, int *> *snakeHeadPos, int x, int y) {
  std::map<int, int *>::iterator it;
  for (it = snakeHeadPos->begin(); it != snakeHeadPos->end(); ++it) {
    if ((it->second)[0] == x && (it->second)[1] == y) {
      shouldPlay = false;
      return;
    }
  }
  if (x > 780 || x < 0 || y > 480 || y < 0) {
    shouldPlay = false;
    return;
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

int drawFrontAnimations(std::vector<int> inputBuf, int x, int y, int frame,
                        int xspd, int yspd, std::map<int, int *> mp) {

  int val = -1;
  auto color = Color(WHITE);
  // front animations
  if (inputBuf.size() > 0) {
    int in = inputBuf[0];
    switch (in) {
    case KEY_DOWN:
      DrawRectangle(x, y + (frame * 4), 20, 20, color);
      break;
    case KEY_UP:
      DrawRectangle(x, y - (frame * 4), 20, 20, color);
      break;
    case KEY_RIGHT:
      DrawRectangle(x + (frame * 4), y, 20, 20, color);
      break;
    case KEY_LEFT:
      DrawRectangle(x - (frame * 4), y, 20, 20, color);
      break;
    }
    val = 2;
  } else {
    int valX = 0;
    int valY = 0;
    if (xspd != 0) {
      valX = frame * 4;
      if (xspd < 0) {
        valX -= valX * 2;
      }
      DrawRectangle(x + valX, y, 20, 20, color);
      val = 0;
    } else {
      int valY = frame * 4;
      if (yspd < 0) {
        valY -= valY * 2;
      }
      DrawRectangle(x, y + valY, 20, 20, color);
      val = 1;
    }
  }

  return val;
}

void checkFoodCollision(std::pair<int, int> snakeHeadPos,
                        std::pair<int, int> *foodPos, int *snakeSize) {
  if (snakeHeadPos.first == foodPos->first) {
    if (snakeHeadPos.second == foodPos->second) {
      DrawText("isOn", 0, 100, 20, Color(WHITE));
      *snakeSize += 1;
      (*foodPos).first = (rand() % 39 + 1) * 20;
      (*foodPos).second = (rand() % 24 + 1) * 20;
    }
  } else {
    DrawText("isOff", 0, 100, 20, Color(WHITE));
    DrawText(std::to_string((*foodPos).first).c_str(), 0, 120, 20,
             Color(WHITE));
    DrawText(std::to_string((*foodPos).second).c_str(), 0, 140, 20,
             Color(WHITE));
  }
}

void drawBackAnimations(int *secondToLastPos, int *lastCoords, int frame,
                        bool hasGrown) {
  // back animations
  int moveXval = lastCoords[0];
  int add = frame * 4;
  int diffValX = lastCoords[0] - secondToLastPos[0];
  int diffValY = lastCoords[1] - secondToLastPos[1];

  int moveYval = lastCoords[1];

  DrawText(std::to_string(lastCoords[0]).c_str(), 0, 18, 16, Color(WHITE));
  DrawText(std::to_string(secondToLastPos[0]).c_str(), 0, 36, 16, Color(WHITE));
  DrawText(std::to_string(diffValX).c_str(), 0, 54, 16, Color(WHITE));

  if (!hasGrown) {
    if (diffValX < 0) {
      moveXval += frame * 4;
    }
    if (diffValX > 0) {
      moveXval -= frame * 4;
    }

    if (diffValY < 0) {
      moveYval += frame * 4;
    }
    if (diffValY > 0) {
      moveYval -= frame * 4;
    }
    DrawText(std::to_string(moveXval).c_str(), 0, 70, 16, Color(WHITE));
    DrawRectangle(moveXval, moveYval, 20, 20, Color(WHITE));
  } else {
    DrawText("isGrowing", 500, 0, 20, Color(WHITE));
  }
}

int main() {
  InitWindow(SCR_W, SCR_H, "testWindow");

  std::map<int, int *> m;
  m[0] = new int[2]{240, 240};

  int size = 10;
  int count = 1;

  int lastKey = KEY_DOWN;
  int xspd;
  int yspd;

  std::pair<int, int> foodPos = std::make_pair(240, 300);

  int timeCount = 0;
  int *arr;
  arr[0] = 0;
  arr[1] = 1;
  std::vector<int> inputBuffer;
  inputBuffer.push_back(KEY_DOWN);
  int hasBuf;

  int *secondToLastCoords = new int[2]{m[0][0], m[0][1]};

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

      checkKeys(&lastKey, &inputBuffer);
      if (shouldPlay) {
        drawBackAnimations(secondToLastCoords, m.begin()->second, timeCount,
                           (size != m.size()));
      }
      if (timeCount >= 5 && shouldPlay) {
        executeInput(&inputBuffer, &xspd, &yspd);
        arr = snakeQueue(&m, xspd, yspd, count, size, (size != m.size()));
        checkFoodCollision(std::make_pair(m[count][0], m[count][1]), &foodPos,
                           &size);
        count++;
        timeCount = 0;
      } else {
        if (shouldPlay) {
          hasBuf = drawFrontAnimations(inputBuffer, arr[0], arr[1], timeCount,
                                       xspd, yspd, m);
        }
      }
      DrawText(std::to_string(hasBuf).c_str(), 400, 0, 20, Color(WHITE));
      // loop to draw snakes
      std::map<int, int *>::iterator it;
      it = m.begin();
      int countDrawnFrames = 0;
      for (it = ++it; it != m.end(); ++it) {
        countDrawnFrames++;
        if (countDrawnFrames == 1) {
          secondToLastCoords[0] = it->second[0];
          secondToLastCoords[1] = it->second[1];
        }
        DrawRectangle((it->second)[0], (it->second)[1], 20, 20, Color(WHITE));
      }
      DrawRectangle(foodPos.first, foodPos.second, 20, 20, Color(BLUE));
      EndDrawing();
    }
  }
  CloseWindow();
  return 0;
}
