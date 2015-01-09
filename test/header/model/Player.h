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
    std::string plays();
    void playsFirstRound();
    /*deprecated*/
    //std::string findBestWordFromSet(std::set<std::string>);
    std::string findWords(std::string, s_pos, int); //int : methode de recherche
    void takeLetters(int nbLetters);
    std::string getLettersFromRack();
    int getNbLetters();


private:
    GameBoard *gameboard;
    Bundle *bundle;
    char rack[7];
    int numberOfLettersOnRack;
};

#endif	/* PLAYER_H */

