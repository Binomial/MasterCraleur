
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
    //@TODO

    // Letter *2
    //@TODO

    //init anchors
    int key = 77;
    s_pos anchor;
    anchor.abs = 7;
    anchor.ord = 7;
    anchors.insert(std::pair<int, s_pos>(key, anchor));
    /* Pourquoi une map avec key = absord ?
     * je voulais un set de struct (x,y);
     * -surcharge operateur == ok
     * -hash : rien compris
     */
}

bool GameBoard::isFreeCase(int x, int y) {
    if (x >= 0 && y >= 0 && x < 15 && y < 15)
        return gameBoard[x][y].letter == ' ';
    else return true;
}

void GameBoard::putLetter(char letter, int x, int y) {
    if (isFreeCase(x, y)) {
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

void GameBoard::addAnchor(int x, int y) {
    if (isFreeCase(x, y) && x > 0 && y > 0 && x < 15 && y < 15) {
        s_pos anchor;
        anchor.abs = x;
        anchor.ord = y;
        anchors.insert(std::pair<int, s_pos>(x * 10 + y, anchor));
    }
}

void GameBoard::upDateAnchors(s_pos beginWord, int length, int direction) {

    if (direction == 0) {//horizontal
        //ajout des ancres au-dessus et en dessous
        for (int i = beginWord.abs; i < beginWord.abs + length; ++i) {
            //retrait des ancres ou on a mis le mot
            anchors.erase(i * 10 + beginWord.ord);
            addAnchor(i, beginWord.ord - 1);
            addAnchor(i, beginWord.ord + 1);
        }
        //devant et derriere
        addAnchor(beginWord.abs - 1, beginWord.ord);
        addAnchor(beginWord.abs + length, beginWord.ord);
    } else {//vertical
        //ajout des ancres gauches et droites
        for (int i = beginWord.ord; i < beginWord.ord + length; ++i) {
            //retrait des ancres ou on a mis le mot
            anchors.erase(beginWord.abs * 10 + i);
            addAnchor(beginWord.abs - 1, i);
            addAnchor(beginWord.abs + 1, i);
        }
        //dessus et dessous
        addAnchor(beginWord.abs, beginWord.ord - 1);
        addAnchor(beginWord.abs, beginWord.ord + length);
    }
}

