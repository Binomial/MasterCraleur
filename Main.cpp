/*
 * File:   Main.cpp
 * Author: jeremy
 *
 * Created on 22 novembre 2014, 14:10
 */

#include <cstdlib>
#include "header/controller/anagramstring/Permut.h"
#include "header/controller/anagramint/Dictionnary.h"
#include "header/controller/anagramint/FindWord.h"
#include "header/model/Bundle.h"
#include "header/model/GameBoard.h"

#include "header/model/Player.h"

using namespace std;

int main() {

    Player *player = new Player();
    int step = 0;
    while (step < 2) {
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "#Tour de jeu numéro " << step << std::endl;
        std::cout << std::endl;
        player->plays();
        step++;
    }


    return 0;
}

