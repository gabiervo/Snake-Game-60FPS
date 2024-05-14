#include "/usr/local/Cellar/raylib/5.0/include/raylib.h"
#include <cmath>
#include <filesystem>
#include <map>
#include <string>
#include <utility>
#include <vector>

// remember that both SCR_W and SCR_H need to always be multiples of TILE_SIZE
#define SCR_W 500
#define SCR_H 1000

#define TILE_SIZE 20

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
void drawEyes(char characterDirection, int x, int y){
  int posX1 = -1;
  int posY1 = -1;

  int posX2 = -1;
  int posY2 = -1;
  if(characterDirection == 'r'){
    posX1 = x + 13;
    posX2 = posX1;

    posY1 = y + 2;
    posY2 = y + 13;
  }
  if(characterDirection == 'l'){
    posX1 = x + 3;
    posX2 = posX1;

    posY1 = y + 2;
    posY2 = y + 13;
  }
  if(characterDirection == 'u'){
    posX1 = x + 2;
    posX2 = x + 13;

    posY1 = y + 3;
    posY2 = posY1;
  }
  if(characterDirection == 'd'){
    posX1 = x + 2;
    posX2 = x + 13;

    posY1 = y + 14;
    posY2 = posY1;
  }

  if(posX1 != -1){
    //DrawText(std::to_string(posX1).c_str(), 0, 400, 16, Color(WHITE));
    DrawRectangle(posX1, posY1, 5, 5, Color(BLUE));
    DrawRectangle(posX2, posY2, 5, 5, Color(BLUE));
  }
}

char executeInput(std::vector<int> *buffer, int *xspd, int *yspd, char prevDirection) {
  char dir = prevDirection; 
  if (buffer->size() > 0) {
    if ((*buffer)[0] == KEY_DOWN && *yspd != -20) {
      *xspd = 0;
      *yspd = 20;
      dir = 'd';
    }
    if ((*buffer)[0] == KEY_UP && *yspd != 20) {
      *xspd = 0;
      *yspd = -20;
      dir = 'u';
    }
    if ((*buffer)[0] == KEY_RIGHT && *xspd != -20) {
      *xspd = 20;
      *yspd = 0;
      dir = 'r';
    }
    if ((*buffer)[0] == KEY_LEFT && *xspd != 20) {
      *xspd = -20;
      *yspd = 0;
      dir = 'l';
    }
    *buffer->erase(buffer->begin());
  }
  return dir;
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
  if (x > SCR_W - TILE_SIZE || x < 0 || y > SCR_H - TILE_SIZE || y < 0) {
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

      // eyes
      DrawRectangle(x + 2, y + (frame * 4) + 14, 5, 5, Color(BLUE));
      DrawRectangle(x + 13, y + (frame * 4) + 14, 5, 5, Color(BLUE));
      break;
    case KEY_UP:
      DrawRectangle(x, y - (frame * 4), 20, 20, color);

      // eyes
      DrawRectangle(x + 2, y - (frame * 4) + 2, 5, 5, Color(BLUE));
      DrawRectangle(x + 13, y - (frame * 4) + 2, 5, 5, Color(BLUE));
      break;
    case KEY_RIGHT:
      DrawRectangle(x + (frame * 4), y, 20, 20, color);

      //eyes
      DrawRectangle(x + (frame * 4) + 13, y + 2, 5, 5,
		      Color(BLUE));
      DrawRectangle(x + (frame * 4) + 13, y + 13, 5, 5,
		      Color(BLUE));
      break;
    case KEY_LEFT:
      DrawRectangle(x - (frame * 4), y, 20, 20, color);
	
      //eyes
      DrawRectangle(x - (frame * 4) + 3, y + 2, 5, 5,
		      Color(BLUE));
      DrawRectangle(x - (frame * 4) + 3, y + 13, 5, 5,
		      Color(BLUE));

      break;
    }
    val = 2;
  } else {
    int valX = 0;
    int valY = 0;
    // if moving horizontally
    if (xspd != 0) {
      valX = frame * 4;
      if (xspd < 0) {
        valX -= valX * 2;
      }
      DrawRectangle(x + valX, y, 20, 20, color);

      //eyes
      int finalValX = x + valX + (valX < 0) * 3 + (valX > 0) * 13;
      DrawRectangle(finalValX, y + 2, 5, 5,
                    Color(BLUE));
      DrawRectangle(x + valX + (valX < 0) * 3 + (valX > 0) * 13, y + 13, 5, 5,
                    Color(BLUE));
      DrawText(std::to_string(finalValX).c_str(), 0, 450, 16, Color(WHITE));
      val = 0;
      // if moving vertically
    } else {
      int valY = frame * 4;
      if (yspd < 0) {
        // going down
        valY -= valY * 2;
      }
      DrawRectangle(x, y + valY, 20, 20, color);

      // eyes
      DrawRectangle(x + 2, y + valY + (valY < 0) * 3 + (valY > 0) * 14, 5, 5,
                    Color(BLUE));
      DrawRectangle(x + 13, y + valY + (valY < 0) * 3 + (valY > 0) * 14, 5, 5,
                    Color(BLUE));
      val = 1;
    }
  }

  return val;
}

void checkFoodCollision(std::pair<int, int> snakeHeadPos,
                        std::pair<int, int> *foodPos, int *snakeSize) {
  if (snakeHeadPos.first == foodPos->first) {
    // if collides change food position
    if (snakeHeadPos.second == foodPos->second) {
      DrawText("isOn", 0, 100, 20, Color(WHITE));
      *snakeSize += 1;

      //-1 and +1 to prevent rand() from returning nums bigger than screen size
      (*foodPos).first = (rand() % ((SCR_W / TILE_SIZE) - 1)) * TILE_SIZE;
      (*foodPos).second = (rand() % ((SCR_H / TILE_SIZE) - 1)) * TILE_SIZE;
    }
  } else {
    // DrawText("isOff", 0, 100, 20, Color(WHITE));
    // DrawText(std::to_string((*foodPos).first).c_str(), 0, 120, 20,
    //        Color(WHITE));
    // DrawText(std::to_string((*foodPos).second).c_str(), 0, 140, 20,
    //      Color(WHITE));
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

  // remember to change initial snake position when changing screen size (if
  // necessary)
  m[0] = new int[2]{200, 240};

  int size = 2;
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
  char dir = 'd';
  bool shouldDoFrontAnimations = false;

  int *secondToLastCoords = new int[2]{m[0][0], m[0][1]};

  SetTargetFPS(60);
  if (IsWindowReady()) {
    if(size == 1){
      shouldPlay = false;
    }
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
        dir = executeInput(&inputBuffer, &xspd, &yspd, dir);
        arr = snakeQueue(&m, xspd, yspd, count, size, (size != m.size()));
        checkFoodCollision(std::make_pair(m[count][0], m[count][1]), &foodPos,
            &size);
        count++;
        timeCount = 0;
        shouldDoFrontAnimations = false;
      } else {
        if (shouldPlay) {
          shouldDoFrontAnimations = true;
        }
      }
      DrawText(std::to_string(dir).c_str(), 0, 200, 20, Color(WHITE));
      DrawText(std::to_string(hasBuf).c_str(), 400, 0, 20, Color(WHITE));
      // loop to draw snakes
      std::map<int, int *>::iterator it;
      it = m.begin();
      int countDrawnFrames = 0;
      for (it = ++it; it != m.end(); ++it) {
        countDrawnFrames++;

        //fetch frames for second to last object to draw back
        if (countDrawnFrames == 1) {
          secondToLastCoords[0] = it->second[0];
          secondToLastCoords[1] = it->second[1];
        }
        DrawRectangle((it->second)[0], (it->second)[1], 20, 20, Color(WHITE));
        if(timeCount == 0 && countDrawnFrames == m.size()-1){
          //DrawText("drawing eyes", 0, 300, 16, Color(WHITE));
          drawEyes(dir, (it->second)[0], (it->second)[1] );
        }
      }
      if(shouldDoFrontAnimations){
        hasBuf = drawFrontAnimations(inputBuffer, arr[0], arr[1], timeCount,
            xspd, yspd, m);
      }
      DrawRectangle(foodPos.first, foodPos.second, 20, 20, Color(BLUE));
      EndDrawing();
    }
  }
  CloseWindow();
  return 0;
}
