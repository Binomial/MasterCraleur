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
    for (int i = 7 - nbLetters; i < 7; i++) {
        if (bundle->isEmpty()) {
            numberOfLettersOnRack -= nbLetters - i;
            std::cout << "WARNING!!! {Paquet vide}" << std::endl;
            break;
        } else {
            rack[i] = bundle->takeLetter();
        }
    }
}

/* Renvoie sous forme de chaine les lettres du chevalet */
std::string Player::getLettersFromRack() {
    std::string result = "";
    for (int i = 0; i < numberOfLettersOnRack; i++) {
        result += rack[i];
    }
    return result;
}

void Player::setNbLetters(int nb) {
    this->numberOfLettersOnRack = nb;
}

std::string Player::getLettersFromRackForGUI() {
    std::string result = "";
    for (int i = 0; i < 7; i++) {
        result += rack[i];
    }
    return result;
}

int Player::getNbLetters() {
    return numberOfLettersOnRack;
}

void Player::updateRack(std::string word) {
    std::cout << getLettersFromRack() << "(debut)" << std::endl;
    int save = 7 - word.length();
    std::cout << "suppression  des lettres du chevalet" << std::endl;

    for (int i = 0; i < 7; ++i) {
        std::size_t pos;
        pos = word.find(rack[i]);
        if (pos != std::string::npos) {

            rack[i] = ' ';
            std::cout << "pos " << i << ": remplacé par '" << rack[i] << "'." << std::endl;
            word.erase(pos, 1);
        }
    }
    //repositionnement des lettres restantes au debut
    int freePos = 0;
    std::cout << "Replacement des lettres au debut " << std::endl;
    for (int i = 0; i < 7; ++i) {

        if (rack[i] != ' ') {
            if (i != freePos) {
                rack[freePos] = rack[i];
                rack[i] = ' ';
            }
            freePos++;
        }
    }
    numberOfLettersOnRack = save;
    std::cout << getLettersFromRack() << "(fin)" << std::endl;

}

void Player::buildMapSolutions(std::vector<s_solution> vectSol) {
    int count = 0;
    s_solution elementSol;
    if (!solutions.empty()) {
        count = solutions.size();
    }
    while (!vectSol.empty()) {
        elementSol = vectSol.back();
        solutions.insert(std::pair<int, s_solution>(count, elementSol));
        vectSol.pop_back();
        count++;
    }
}

void Player::putWord(std::string wordToPut, int abs, int ord, int vardir) {
    gameboard->putWord(wordToPut, abs, ord, vardir);
}

std::vector<s_solution> Player::findWords(std::string chevalet, s_pos anchor, int method) {
    std::vector<s_solution> vectSol;
    switch (method) {
        case 0:
            Trie *dawg = new Trie();
            //TROP D OUVERTURES DE DICO TROUVER AUTRE MOYEN
            dawg->loadDawg("dict/dictFrDawg.dc");
            vectSol = dawg->findWords(chevalet, *gameboard, anchor);
            break;
            //@TODO
            //case 1: //anagramint
            //   break;
            //case 2: //anagramstring
            //   break;
    }
    return vectSol;
}

std::map<int, s_solution> Player::plays(int meth) {

    solutions.clear();
    std::vector<s_solution> vectSol;
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
    std::cout << std::endl;

    /* Etape 2 : Recherche des mots */
    for (auto const& anchor : gameboard->getAnchors()) {
        vectSol = findWords(letters, anchor.second, meth);
        buildMapSolutions(vectSol);
    }

    return solutions;
    /* Etape 3 : Calcul des points*/
    //@TODO


}

void Player::upDate(s_solution solution, bool updateRac) {
    /*Etape 5 : Mise à jour des ancres */
    s_pos begin;
    begin.abs = solution.abs;
    begin.ord = solution.ord;
    gameboard->upDateAnchors(begin, solution.word.length(), solution.dir);

    /* Etape 6 : Modification du chevalet */
    if(updateRac)
        updateRack(solution.word);
}

GameBoard Player::getGameBoard() {
    return *gameboard;
}

void Player::deleteLetter(char c) {
    bundle->deleteLetter(c);
}