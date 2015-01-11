#include "../../header/model/Player.h"

/* CONSTRUCTEUR*/
Player::Player() {
    bundle = new Bundle();
    bundle->init();
    gameboard = new GameBoard();
    gameboard->init();
    for (int i = 0; i < 7; ++i)
        rack[i] = ' ';
    numberOfLettersOnRack = 0;
}

/* Ajoute au chevalet "nbLetters" lettres , met a jour numberOfLettersOnRack*/
void Player::takeLetters(int nbLetters) {
    numberOfLettersOnRack = 7; //si tt se passe bien, y aura 7 lettres. Sinon, c'est traité en dessous.
    for (int i = 0; i < nbLetters; i++) {
        if (bundle->isEmpty()) {
            numberOfLettersOnRack -= nbLetters - i;
            std::cout << "WARNING!!! {Paquet vide}" << std::endl;
            break;
        } else {
            rack[i] = bundle->takeLetter();
        }
    }
    std::cout << std::endl;
}

/* Renvoie sous forme de chaine les lettres du chevalet */
std::string Player::getLettersFromRack() {
    std::string result = "";
    for (int i = 0; i < numberOfLettersOnRack; i++) {
        result += rack[i];
    }
    return result;
}

int Player::getNbLetters() {
    return numberOfLettersOnRack;
}

void Player::updateRack(std::string word) {
    numberOfLettersOnRack = 7 - word.length();
    //retrait des lettres dans le chevalet
    for (int i = 0; i < 7; ++i) {
        std::size_t pos;
        pos = word.find(rack[i]);
        if (pos != std::string::npos) {
            rack[i] = ' ';
            word.erase(pos, 1);
        }
    }
    //repositionnement des lettres restantes à la fin
    int freePos = 6;
    for (int i = 6; i > -1; --i) {
        if (rack[i] != ' ') {
            if (i != freePos) {
                rack[freePos] = rack[i];
                rack[i] = ' ';
            }
            freePos--;
        }
    }
}

void Player::findWords(std::string chevalet, s_pos anchor, int method) {
    std::set<std::string> solutions;
    switch (method) {
        case 0:
            Trie *dawg = new Trie();
            //TROP D OUVERTURES DE DICO TROUVER AUTRE MOYEN
            dawg->loadDawg("dict/dictFrDawg.dc");
            solutions = dawg->findWords(chevalet, *gameboard, anchor);

            for (auto const& sol : solutions) {
                std::cout << sol << std::endl;
            }
            break;
            //@TODO
            //case 1: //anagramint
            //   break;
            //case 2: //anagramstring
            //   break;
    }
}

void Player::plays(int meth) {

    std::string letters = "";

    /* Etape 1 : On remplit le chevalet */
    takeLetters(7 - numberOfLettersOnRack);
    letters = getLettersFromRack();


    /*Affichage */
    bundle->displayDebug();
    std::cout << "Chevalet(" << numberOfLettersOnRack << ") : <" << letters << ">" << std::endl;
    std::cout << std::endl;
    std::cout << "Ancres(" << gameboard->getAnchors().size() << ") " << std::endl;
    std::cout << std::endl;
    Console::display(*gameboard);
    std::cout << std::endl;

    /* Etape 2 : Recherche des mots */
    for (auto const& anchor : gameboard->getAnchors()) {
        findWords(letters, anchor.second, meth);
    }

    /* Etape 3 : Calcul des points*/
    //@TODO

    /* Etape 4 : Choix d'un mot */
    std::string wordToPut = "";
    int abs = 0;
    int ord = 0;
    int vardir = 0;
    std::cout << "Choisir mot a placer" << std::endl;
    std::cin >> wordToPut;
    std::cout << "abs ?" << std::endl;
    std::cin >> abs;
    std::cout << "ord ?" << std::endl;
    std::cin >> ord;
    std::cout << "dir ?" << std::endl;
    std::cin >> vardir;

    /* Etape 4 : Placement du mot */
    gameboard->putWord(wordToPut, abs, ord, vardir); // putWord("mot", abs, ord, direction)

    /*Etape 5 : Mise à jour des ancres */
    s_pos begin;
    begin.abs = abs;
    begin.ord = ord;
    gameboard->upDateAnchors(begin, wordToPut.length(), vardir);

    /* Etape 6 : Modification du chevalet */
    updateRack(wordToPut);


    /* Affichage */
    Console::display(*gameboard);

}


