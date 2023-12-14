// SnakeGame.cpp

#include "SnakeGame.h"

Coordinates::Coordinates() : x(0), y(0) {}
Coordinates::Coordinates(int newX, int newY) : x(newX), y(newY) {}

SnakeHead::SnakeHead() : direction(0) {}
SnakeHead::SnakeHead(const Coordinates& pos, int dir) : position(pos), direction(dir) {}

MapCell::MapCell() : value(0) {}
MapCell::MapCell(int val) : value(val) {}

SnakeGame::SnakeGame() : map(20 * 20), food(4), running(true) {
    initMap();
}

void SnakeGame::run() {
    while (running) {
        if (_kbhit()) {
            changeDirection(_getch());
        }
        update();
        clearScreen();
        printMap();
        Sleep(400);
    }

    cout << "\t\tGame Over!" << endl << "\t\tYour score is: " << food << endl;
    cin.ignore();
}

void SnakeGame::initMap() {
    srand(static_cast<unsigned>(time(0)));

    snakeHead = SnakeHead(Coordinates(10, 10), 0);

    for (int x = 0; x < 20; ++x) {
        map[x] = MapCell(-1);
        map[x + 19 * 20] = MapCell(-1);
    }

    for (int y = 0; y < 20; y++) {
        map[0 + y * 20] = MapCell(-1);
        map[19 + y * 20] = MapCell(-1);
    }

    generateFood();
}

void SnakeGame::printMap() {
    for (int x = 0; x < 20; ++x) {
        for (int y = 0; y < 20; ++y) {
            cout << getMapValue(map[x + y * 20]);
        }
        cout << endl;
    }
}

void SnakeGame::generateFood() {
    int x, y;
    do {
        x = rand() % 18 + 1;
        y = rand() % 18 + 1;
    } while (map[x + y * 20].value != 0);

    map[x + y * 20] = MapCell(-2);
}

void SnakeGame::update() {
    switch (snakeHead.direction) {
    case 0: move(-1, 0); break;
    case 1: move(0, 1); break;
    case 2: move(1, 0); break;
    case 3: move(0, -1); break;
    }

    for (int i = 0; i < 20 * 20; i++) {
        if (map[i].value > 0) map[i].value--;
    }
}

void SnakeGame::move(int dx, int dy) {
    int newx = snakeHead.position.x + dx;
    int newy = snakeHead.position.y + dy;

    if (map[newx + newy * 20].value == -2) {
        food++;
        generateFood();
    } else if (map[newx + newy * 20].value != 0) {
        running = false;
    }

    snakeHead.position.x = newx;
    snakeHead.position.y = newy;
    map[newx + newy * 20] = MapCell(food + 1);
}

void SnakeGame::changeDirection(char key) {
    switch (key) {
    case 'w': if (snakeHead.direction != 2) snakeHead.direction = 0; break;
    case 'd': if (snakeHead.direction != 3) snakeHead.direction = 1; break;
    case 's': if (snakeHead.direction != 0) snakeHead.direction = 2; break;
    case 'a': if (snakeHead.direction != 1) snakeHead.direction = 3; break;
    }
}

void SnakeGame::clearScreen() {
    system("cls");
}

char SnakeGame::getMapValue(const MapCell& cell) {
    if (cell.value > 0) return 'o';
    switch (cell.value) {
    case -1: return 'X';
    case -2: return 'O';
    default: return ' ';
    }
}
