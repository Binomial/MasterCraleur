/*
 * File:   GameBoard.h
 * Author: jeremy
 *
 * Created on 12 décembre 2014, 17:41
 */

#ifndef GAMEBOARD_H
#define	GAMEBOARD_H

#include "Bundle.h"
#include <set>

typedef struct {
    int coef;
    char letter; // ' ' si pas de lettre
} s_case;

//struct t_pos {
//    int abs;
//    int ord; // ' ' si pas de lettre
//
//    bool operator==(t_pos const &p) const {
//        return false; //((p.abs == p2.abs) && (p.ord == p2.ord));
//    }
//};

typedef struct {
    int abs;
    int ord; // ' ' si pas de lettre
} s_pos;

//inline bool operator<(s_pos const &p, s_pos const &p2) {
//    return (((p.abs < p2.abs) && (p.ord == p2.ord)) || ((p.abs == p2.abs) && (p.ord < p2.ord)));
//}

class GameBoard {
public:
    void init();
    bool isFreeCase(int, int); // x, y
    void putLetter(char, int, int); //Letter, x and y position
    void putWord(std::string, int, int, int); //mot, abscisse, ordonnee, direction
    char getLetter(int, int); // x, y
    int getCoef(int, int);
    std::map<int, s_pos> getAnchors();
    void upDateAnchors(s_pos, int, int);
private:
    //std::set<s_pos> anchors;
    std::map<int, s_pos> anchors;
    s_case gameBoard[15][15];
};

#endif	/* GAMEBOARD_H */

