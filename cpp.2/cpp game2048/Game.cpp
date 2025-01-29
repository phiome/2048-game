#include "Game.h"
#include <iostream>

void Game::start() {
    std::string input; // std::string olarak değiştirdik
    while (true) {
        render();
        std::cout << "Hareket (W, A, S, D) veya çıkmak için Q: ";
        
        std::getline(std::cin, input); // std::cin yerine std::getline kullandık

        if (input.length() == 1) { // Tek karakter alındığından emin olalım
            char move = input[0];
            bool validMove = processInput(move);
            if (validMove) {
                update();
            }
        } else {
            std::cout << "Geçersiz giriş! Lütfen yalnızca tek bir harf girin (W, A, S, D, Q).\n";
        }
    }
}

bool Game::processInput(char input) {
    switch (input) {
        case 'w':
        case 'W':
            board.moveUp();
            return true;
        case 'a':
        case 'A':
            board.moveLeft();
            return true;
        case 's':
        case 'S':
            board.moveDown();
            return true;
        case 'd':
        case 'D':
            board.moveRight();
            return true;
        case 'q':
        case 'Q':
            std::cout << "Çıkılıyor..." << std::endl;
            exit(0);
        default:
            std::cout << "Geçersiz giriş! Lütfen W, A, S, D veya Q tuşlarını kullanın.\n";
            return false;
    }
}

void Game::update() {
    board.addRandomTile();
}

void Game::render() const {
    board.display();
}
