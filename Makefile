all: snake_game

snake_game: main.cpp libSnakeGame.so
    g++ -o snake_game main.cpp -L. -lSnakeGame

libSnakeGame.so: SnakeGame.o
    g++ -shared -o libSnakeGame.so SnakeGame.o

SnakeGame.o: SnakeGame.cpp SnakeGame.h
    g++ -c SnakeGame.cpp -o SnakeGame.o

clean:
    rm -f *.o *.so snake_game
