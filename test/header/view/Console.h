/*
 * File:   Console.h
 * Author: jeremy
 *
 * Created on 12 décembre 2014, 18:32
 */

#ifndef CONSOLE_H
#define	CONSOLE_H

#include <iostream>
#include "../../header/model/GameBoard.h"

class Console {
public:
    static void display(GameBoard);
    static void displayRack(char[7]);
private:


};
#endif	/* CONSOLE_H */

