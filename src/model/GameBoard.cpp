
#include "../../header/model/GameBoard.h"

void GameBoard::init() {

    // Init all case like normal case
    for (int x = 0; x < 15; x++) {
        for (int y = 0; y < 15; y++) {
            gameBoard[x][y].coef = 0;
            gameBoard[x][y].letter = ' ';
        }
    }

    // Word * 3
    gameBoard[0][0].coef = 6;
    gameBoard[7][0].coef = 6;
    gameBoard[14][0].coef = 6;
    gameBoard[0][7].coef = 6;
    gameBoard[14][7].coef = 6;
    gameBoard[0][14].coef = 6;
    gameBoard[7][14].coef = 6;
    gameBoard[14][14].coef = 6;

    // Word * 2
    gameBoard[1][1].coef = 4;
    gameBoard[2][2].coef = 4;
    gameBoard[3][3].coef = 4;
    gameBoard[4][4].coef = 4;

    gameBoard[10][10].coef = 4;
    gameBoard[11][11].coef = 4;
    gameBoard[12][12].coef = 4;
    gameBoard[13][13].coef = 4;

    gameBoard[1][13].coef = 4;
    gameBoard[2][12].coef = 4;
    gameBoard[3][11].coef = 4;
    gameBoard[4][10].coef = 4;

    gameBoard[10][4].coef = 4;
    gameBoard[11][3].coef = 4;
    gameBoard[12][2].coef = 4;
    gameBoard[13][1].coef = 4;


    // Letter * 3


    // Letter *2

    //init anchors
    s_pos anchor;
    anchor.abs = 7;
    anchor.ord = 7;
    int key = 77;
    anchors.insert(std::pair<int, s_pos>(key, anchor));
}

bool GameBoard::isFreeCase(int x, int y) {
    return gameBoard[x][y].letter == ' ';
}

void GameBoard::putLetter(char letter, int x, int y) {
    if (isFreeCase(x, y)) {
        //std::cout << "je put la letter '" << letter << "' à la position (" << x << ", " << y << " )" << std::endl;
        gameBoard[x][y].letter = letter;
    }
}

char GameBoard::getLetter(int x, int y) {
    return gameBoard[x][y].letter;
}

int GameBoard::getCoef(int x, int y) {
    return gameBoard[x][y].coef;
}

void GameBoard::putWord(std::string word, int abs, int ord, int dir) {
    for (int i = 0; i < word.length(); ++i) {
        (dir == 0) ? putLetter(word[i], abs + i, ord) : putLetter(word[i], abs, ord + i);
    }
}

std::map<int, s_pos> GameBoard::getAnchors() {
    return anchors;
}

void GameBoard::upDateAnchors(s_pos beginWord, int length, int direction) {

    if (direction == 0) {//horizontal
        for (int i = beginWord.abs; i < beginWord.abs + length; ++i) {
            //retrait des ancres ou on a mis le mot
            anchors.erase(i * 10 + beginWord.ord);

            if (isFreeCase(i, beginWord.ord - 1)) {
                s_pos anchorUp;
                anchorUp.abs = i;
                anchorUp.ord = beginWord.ord - 1;
                anchors.insert(std::pair<int, s_pos>(i * 10 + beginWord.ord - 1, anchorUp));
            }
            if (isFreeCase(i, beginWord.ord + 1)) {
                s_pos anchor;
                anchor.abs = i;
                anchor.ord = beginWord.ord + 1;
                anchors.insert(std::pair<int, s_pos>(i * 10 + beginWord.ord + 1, anchor));
            }
        }
    }

    for (auto const& anchor : anchors) {
        std::cout << "(" << anchor.second.abs << "," << anchor.second.ord << ")" << std::endl;
    }
}