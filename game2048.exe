#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Game2048 {
private:
    std::vector<std::vector<int>> board;
    int size;

    // Rastgele boş bir hücreye 2 veya 4 yerleştirir
    void addRandomTile() {
        std::vector<std::pair<int, int>> emptyCells;

        // Boş hücreleri bul
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (board[i][j] == 0) {
                    emptyCells.push_back({i, j});
                }
            }
        }

        // Eğer boş hücre yoksa, çık
        if (emptyCells.empty()) return;

        // Rastgele bir boş hücre seç
        int randomIndex = rand() % emptyCells.size();
        int row = emptyCells[randomIndex].first;
        int col = emptyCells[randomIndex].second;

        // Rastgele olarak 2 veya
