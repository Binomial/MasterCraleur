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


class Player {
public :
    void takeLetters(int nbLetters);
private:
    //GameBoard gameBoard;
    Bundle bundle;
    s_letter rack[7];
};

#endif	/* PLAYER_H */

