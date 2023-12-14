#include "SnakeGame.h"

SnakeHead::SnakeHead() : direction(0) {}
SnakeHead::SnakeHead(const Coordinates& pos, int dir) : position(pos), direction(dir) {}
