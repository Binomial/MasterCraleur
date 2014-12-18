/*
 * File:   GameBoard.h
 * Author: jeremy
 *
 * Created on 12 décembre 2014, 17:41
 */

#ifndef GAMEBOARD_H
#define	GAMEBOARD_H

#include "Bundle.h"

typedef struct {
    int coef;
    char letter; // 0 si pas de lettre
} s_case;

class GameBoard {
public:
    void init();
    bool isFreeCase(int, int); // x, y
    void putLetter(char, int, int); //Letter, x and y position
    char getLetter(int, int); // x, y
    int getCoef(int, int);
private:
    s_case gameBoard[15][15];
};

#endif	/* GAMEBOARD_H */

