#include "../../header/model/Player.h"



void Player::takeLetters(int nbLetters) {
    for (int i = 0; i < nbLetters; i++) {
        if(bundle.isEmpty()) {
            break;
        } else {
            rack[7-nbLetters-1+i] = bundle.takeLetter();
        }
    }
}

