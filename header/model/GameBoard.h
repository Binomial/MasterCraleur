/*
 * File:   GameBoard.h
 * Author: jeremy
 *
 * Created on 12 décembre 2014, 17:41
 */

#ifndef GAMEBOARD_H
#define	GAMEBOARD_H

#include "Bundle.h"

#include <fstream>

typedef struct {
    int coef;
    char letter; // ' ' si pas de lettre
} s_case;

class GameBoard {
public:
    void init();
    bool isFreeCase(int, int); // x, y
    void putLetter(char, int, int); //Letter, x and y position
    void putWord(std::string, int, int, int); //mot, abscisse, ordonnee, direction
    char getLetter(int, int); // x, y
    int getCoef(int, int);
    void importGameBoard(std::string);
private:
    s_case gameBoard[15][15];
};

#endif	/* GAMEBOARD_H */

