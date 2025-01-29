#include "Board.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <algorithm> // std::reverse için eklendi

Board::Board() : grid(4, std::vector<int>(4, 0)) {
    std::srand(std::time(0));
    addRandomTile();
    addRandomTile();
}

void Board::moveUp() {
    rotateClockwise();
    moveLeft();
    rotateCounterClockwise();
}

void Board::moveDown() {
    rotateCounterClockwise();
    moveLeft();
    rotateClockwise();
}

void Board::moveLeft() {
    for (auto& row : grid) {
        std::vector<int> newRow;
        for (int val : row) {
            if (val != 0) newRow.push_back(val);
        }
        for (size_t i = 0; i < newRow.size() - 1; ++i) {
            if (newRow[i] == newRow[i + 1]) {
                newRow[i] *= 2;
                newRow.erase(newRow.begin() + i + 1);
            }
        }
        row = newRow;
        row.resize(4, 0);
    }
}

void Board::moveRight() {
    for (auto& row : grid) {
        std::reverse(row.begin(), row.end()); // std::reverse hata veriyordu, düzelttim
    }
    moveLeft();
    for (auto& row : grid) {
        std::reverse(row.begin(), row.end());
    }
}

void Board::addRandomTile() {
    std::vector<std::pair<int, int>> emptyCells;
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            if (grid[r][c] == 0) {
                emptyCells.emplace_back(r, c);
            }
        }
    }
    if (!emptyCells.empty()) {
        auto [r, c] = emptyCells[std::rand() % emptyCells.size()];
        grid[r][c] = (std::rand() % 2 + 1) * 2;
    }
}

void Board::display() const {
    for (const auto& row : grid) {
        for (int val : row) {
            if (val == 0) {
                std::cout << std::setw(4) << ".";
            } else {
                std::cout << std::setw(4) << val;
            }
        }
        std::cout << std::endl;
    }
}

void Board::rotateClockwise() {
    std::vector<std::vector<int>> newGrid(4, std::vector<int>(4, 0));
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            newGrid[c][3 - r] = grid[r][c];
        }
    }
    grid = newGrid;
}

void Board::rotateCounterClockwise() {
    std::vector<std::vector<int>> newGrid(4, std::vector<int>(4, 0));
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            newGrid[3 - c][r] = grid[r][c];
        }
    }
    grid = newGrid;
}
