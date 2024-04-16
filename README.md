A simple snake game made with raylib in c++ that just has smooth snake movement with a very simple implementation using queues and interpolation.

The GitHub already has a pre-compiled build for Mac under the snakeMaps file, but you can compile it yourself using the command below:
**For g++:**
```
g++ snakeMaps.cpp -o snakeMaps -lraylib -std=c++11
```
The oldSnake folder just contains an old build with a different, but considerably worse system that I won't revise anytime soon, but still think can be useful as a learning resource to understand a naive way to approach the snake game problem, and why it doesn't work well.
