#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

struct Coordinates {
    int x;
    int y;

    Coordinates();
    Coordinates(int newX, int newY);
};

struct SnakeHead {
    Coordinates position;
    int direction;

    SnakeHead();
    SnakeHead(const Coordinates& pos, int dir);
};

struct MapCell {
    int value;

    MapCell();
    MapCell(int val);
};

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class SnakeGame {
public:
    SnakeGame();
    void run();

private:
    vector<MapCell> map;
    SnakeHead snakeHead;
    int food;
    bool running;

    void initMap();
    void printMap();
    void generateFood();
    void update();
    void changeDirection(char key);
    void move(int dx, int dy);
    void clearScreen();
    char getMapValue(const MapCell& cell);
};

#endif // SNAKEGAME_H

