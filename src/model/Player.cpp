#include "../../header/model/Player.h"

Player::Player() {
    bundle = new Bundle();
    bundle->init();
    gameboard = new GameBoard();
    gameboard->init();
    for (int i = 0; i < 7; ++i)
        rack[i] = ' ';
}

void Player::takeLetters(int nbLetters) {
    for (int i = 0; i < nbLetters; i++) {
        if (bundle->isEmpty()) {
            std::cout << "t'es vide" << std::endl;
            break;
        } else {
            rack[7 - nbLetters + i] = bundle->takeLetter();
            std::cout << nbLetters << std::endl;
        }
    }
}

std::string Player::getLettersFromRack() {
    std::string result = "";
    //changer 7
    for (int i = 0; i < 7; i++) {
        result += rack[i];
    }
    return result;
}

void Player::plays() {
    bundle->debug();
    Console::display(*gameboard);
    takeLetters(7);
    std::cout << rack << std::endl;
    bundle->debug();
    //faire rechercher un mot, en fonction d'une place
    //trouver le meilleur mot en fonction des points des lettres uniquement
    //placer le mot

}