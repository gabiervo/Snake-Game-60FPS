A simple snake game made with raylib in c++ that just has smooth snake movement with a very simple implementation using queues and interpolation.

The GitHub already has a pre-compiled build for Mac under the snakeMaps file, but you can compile it yourself using the command below: <br>
**Note: remember to change the raylib directory listed in the #include statement to match your raylib file** <br>
**For g++:**
```
g++ snakeMaps.cpp -o snakeMaps -lraylib -std=c++11
```
The oldSnake folder just contains an old build with a different, but considerably worse system that I won't revise anytime soon, but I didn't see any reason not to leave in.

Current good first issues:
- Very hacky drawEyes code, I'd recommend creating new code that just changes the eye position based purely in the direction value and follows the frontAnimations values in one single function, instead of the current implementation that splits up drawing eyes into two functions
