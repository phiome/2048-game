#ifndef GAME_H
#define GAME_H

#include "Board.h"

class Game {
public:
    void start();
private:
    Board board;
    bool processInput(char input); // Buradaki dönüş türü 'bool' olarak değiştirildi!
    void update();
    void render() const;
};

#endif // GAME_H
