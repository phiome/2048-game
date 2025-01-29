#include "game2048.h"
#include <cstdlib>
#include <ctime>

// Constructor
Game2048::Game2048(int boardSize) : size(boardSize) {
    board.resize(size, std::vector<int>(size, 0));
    srand(time(0));
    addRandomTile();
    addRandomTile();
}

// Rastgele bir sayı ekler
void Game2048::addRandomTile() {
    std::vector<std::pair<int, int>> emptyCells;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (board[i][j] == 0) {
                emptyCells.push_back({i, j});
            }
        }
    }

    if (emptyCells.empty()) return;

    int randomIndex = rand() % emptyCells.size();
    int row = emptyCells[randomIndex].first;
    int col = emptyCells[randomIndex].second;

    board[row][col] = (rand() % 2 == 0) ? 2 : 4;
}

// Sola hareket
void Game2048::moveLeft() {
    for (int i = 0; i < size; ++i) {
        std::vector<int> newRow(size, 0);
        int index = 0;

        for (int j = 0; j < size; ++j) {
            if (board[i][j] != 0) {
                newRow[index] = board[i][j];
                index++;
            }
        }

        for (int j = 0; j < size - 1; ++j) {
            if (newRow[j] != 0 && newRow[j] == newRow[j + 1]) {
                newRow[j] *= 2;
                score += newRow[j]; // Puanı güncelle
                newRow[j + 1] = 0;
            }
        }

        std::vector<int> finalRow(size, 0);
        index = 0;
        for (int j = 0; j < size; ++j) {
            if (newRow[j] != 0) {
                finalRow[index] = newRow[j];
                index++;
            }
        }

        board[i] = finalRow;
    }
    addRandomTile();
}

// Sağa hareket
void Game2048::moveRight() {
    for (int i = 0; i < size; ++i) {
        std::vector<int> newRow(size, 0);
        int index = size - 1;

        for (int j = size - 1; j >= 0; --j) {
            if (board[i][j] != 0) {
                newRow[index] = board[i][j];
                index--;
            }
        }

        for (int j = size - 1; j > 0; --j) {
            if (newRow[j] != 0 && newRow[j] == newRow[j - 1]) {
                newRow[j] *= 2;
                score += newRow[j]; // Puanı güncelle
                newRow[j - 1] = 0;
            }
        }

        std::vector<int> finalRow(size, 0);
        index = size - 1;
        for (int j = size - 1; j >= 0; --j) {
            if (newRow[j] != 0) {
                finalRow[index] = newRow[j];
                index--;
            }
        }

        board[i] = finalRow;
    }
    addRandomTile();
}

// Yukarı hareket
void Game2048::moveUp() {
    for (int j = 0; j < size; ++j) {
        std::vector<int> newCol(size, 0);
        int index = 0;

        for (int i = 0; i < size; ++i) {
            if (board[i][j] != 0) {
                newCol[index] = board[i][j];
                index++;
            }
        }

        for (int i = 0; i < size - 1; ++i) {
            if (newCol[i] != 0 && newCol[i] == newCol[i + 1]) {
                newCol[i] *= 2;
                score += newCol[i]; // Puanı güncelle
                newCol[i + 1] = 0;
            }
        }

        std::vector<int> finalCol(size, 0);
        index = 0;
        for (int i = 0; i < size; ++i) {
            if (newCol[i] != 0) {
                finalCol[index] = newCol[i];
                index++;
            }
        }

        for (int i = 0; i < size; ++i) {
            board[i][j] = finalCol[i];
        }
    }
    addRandomTile();
}

// Aşağı hareket
void Game2048::moveDown() {
    for (int j = 0; j < size; ++j) {
        std::vector<int> newCol(size, 0);
        int index = size - 1;

        for (int i = size - 1; i >= 0; --i) {
            if (board[i][j] != 0) {
                newCol[index] = board[i][j];
                index--;
            }
        }

        for (int i = size - 1; i > 0; --i) {
            if (newCol[i] != 0 && newCol[i] == newCol[i - 1]) {
                newCol[i] *= 2;
                score += newCol[i]; // Puanı güncelle
                newCol[i - 1] = 0;
            }
        }

        std::vector<int> finalCol(size, 0);
        index = size - 1;
        for (int i = size - 1; i >= 0; --i) {
            if (newCol[i] != 0) {
                finalCol[index] = newCol[i];
                index--;
            }
        }

        for (int i = 0; i < size; ++i) {
            board[i][j] = finalCol[i];
        }
    }
    addRandomTile();
}

// Kazanma durumu
bool Game2048::checkWin() {
    for (const auto& row : board) {
        for (int cell : row) {
            if (cell == 2048) {
                return true; // Kazanma durumu
            }
        }
    }
    return false;
}

// Kaybetme durumu
bool Game2048::checkLose() {
    for (const auto& row : board) {
        for (int cell : row) {
            if (cell == 0) {
                return false; // Hâlâ boş hücre var
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size - 1; ++j) {
            if (board[i][j] == board[i][j + 1]) {
                return false; // Yatayda birleştirilebilir taş var
            }
        }
    }

    for (int j = 0; j < size; ++j) {
        for (int i = 0; i < size - 1; ++i) {
            if (board[i][j] == board[i + 1][j]) {
                return false; // Dikeyde birleştirilebilir taş var
            }
        }
    }

    return true; // Hiçbir hareket yapılamıyor
}

void Game2048::printBoard() {
    for (const auto& row : board) {
        for (int cell : row) {
            std::cout << (cell == 0 ? "." : std::to_string(cell)) << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "Score: " << score << "\n";
    std::cout << "\n";
}

void Game2048::move(char direction) {
    direction = toupper(direction);
    if (direction == 'L') moveLeft();
    else if (direction == 'R') moveRight();
    else if (direction == 'U') moveUp();
    else if (direction == 'D') moveDown();
}
