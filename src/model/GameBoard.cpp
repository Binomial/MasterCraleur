
#include "../../header/model/GameBoard.h"

void GameBoard::initGameBoard() {
    for(int x = 0; x < 15; x++) {
        for(int y = 0; y < 15; y++) {
            gameBoard[x][y].coef = 0;
            gameBoard[x][y].letter.car = ' ';
        }
    }
    
    gameBoard[0][0].coef = 6;  // Word *3
    gameBoard[7][00].coef = 6;
    gameBoard[14][0].coef = 6;
    gameBoard[0][7].coef = 6;
    gameBoard[14][7].coef = 6;
    gameBoard[0][14].coef = 6;
    gameBoard[7][14].coef = 6;
    gameBoard[14][14].coef = 6;
    
}

bool GameBoard::isFreeCase(int x, int y) {
    return gameBoard[x][y].letter.car == ' ';
}

void GameBoard::putLetter(s_letter letter, int x, int y) {
    if(isFreeCase(x,y)) {
        gameBoard[x][y].letter = letter;   
    }
}

s_letter GameBoard::getLetter(int x, int y) {
    return gameBoard[x][y].letter;
}

int GameBoard::getCoef(int x, int y) {
    return gameBoard[x][y].coef;
}
