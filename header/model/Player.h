/*
 * File:   Player.h
 * Author: jeremy
 *
 * Created on 12 décembre 2014, 17:31
 */

#ifndef PLAYER_H
#define	PLAYER_H


#include <cstdlib>
#include <iostream>
#include "Bundle.h"
#include "../view/Console.h"
#include "../controller/dawg/Trie.h"

class Player {
public:
    Player();
    void plays();
    void playsFirstRound();
    std::string findBestWordFromSet(std::set<std::string>);
    std::string searchBestWord(std::string, int); //int : methode de recherche
    void takeLetters(int nbLetters);
    std::string getLettersFromRack();

private:
    GameBoard *gameboard;
    Bundle *bundle;
    char rack[7];
};

#endif	/* PLAYER_H */

