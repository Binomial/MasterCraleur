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
#include "../controller/dawg/Trie.h"

class Player {
public:
    Player();
    std::map<int, s_solution> plays(int);
    std::vector<s_solution> findWords(std::string, s_pos, int); //int : methode de recherche
    void takeLetters(int nbLetters);
    std::string getLettersFromRack();
    std::string getLettersFromRackForGUI();
    int getNbLetters();
    void updateRack(std::string); //int longueur du mot qui a été placé
    void buildMapSolutions(std::vector<s_solution>);
    void putWord(std::string, int, int, int);
    void upDate(s_solution);
    GameBoard getGameBoard();
private:
    GameBoard *gameboard;
    Bundle *bundle;
    char rack[7];
    int numberOfLettersOnRack;
    std::map<int, s_solution> solutions;
};

#endif	/* PLAYER_H */

