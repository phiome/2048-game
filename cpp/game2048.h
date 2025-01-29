#ifndef GAME2048_H
#define GAME2048_H

#include <vector>
#include <iostream>

class Game2048 {
private:
    std::vector<std::vector<int>> board;
    int size;
    int score = 0;

    void addRandomTile();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

public:
    Game2048(int boardSize);
    void printBoard();
    void move(char direction);
    bool checkWin();
    bool checkLose();
};

#endif // GAME2048_H
