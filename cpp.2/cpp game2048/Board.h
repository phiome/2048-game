#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board {
public:
    Board();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void addRandomTile();
    void display() const;
private:
    std::vector<std::vector<int>> grid;
    void rotateClockwise();
    void rotateCounterClockwise();
    bool canMove() const;
};

#endif // BOARD_H
