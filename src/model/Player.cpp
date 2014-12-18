#include "../../header/model/Player.h"

Player::Player() {
    bundle = new Bundle();
    bundle->init();
    gameboard = new GameBoard();
    gameboard->init();
    for (int i = 0; i < 7; ++i)
        rack[i] = ' ';
}

void Player::takeLetters(int nbLetters) {
    std::cout << "Lettres tirées : ";
    for (int i = 0; i < nbLetters; i++) {
        if (bundle->isEmpty()) {
            std::cout << "t'es vide..." << std::endl;
            break;
        } else {
            rack[7 - nbLetters + i] = bundle->takeLetter();
            std::cout << rack[7 - nbLetters + i] << " ";
        }
    }
    std::cout << std::endl;
}

std::string Player::getLettersFromRack() {
    std::string result = "";
    //changer 7
    for (int i = 0; i < 7; i++) {
        result += rack[i];
    }
    return result;
}

std::string Player::findBestWordFromSet(std::set<std::string> solutions) {
    std::string bestWord = "";
    int points;
    int bestPoints = 0;
    std::cout << "Debut du for" << std::endl;
    for (const auto& word : solutions) {
        points = 0;
        std::cout << word << std::endl;
        for (int i = 0; i < word.length(); ++i) {
            points += 1; // ici je cherche juste le mot le plus long en rajoutant +1 a chq lettre, mais en vrai on aura une map<'lettre',int> et on renverra le int qui correspond à word[i]
        }
        if (points > bestPoints) {
            bestPoints = points;
            bestWord = word;
        }
    }
    std::cout << "Meilleur mot = " << bestWord << std::endl;
    return bestWord;
}

std::string Player::searchBestWord(std::string chevalet) {
    //lancer une recherche avec les lettres
    std::set<std::string> solutions;
    //Pour l'instant je fais avec Dawg, apres on mettra un parametre a searchBestWord pour preciser quelle methode
    //DEBUT DU SWITCH
    //case : parametre = 0 -> Dawg
    Trie *dawg = new Trie();
    dawg->loadDawg("dict/dictFrDawg.dc");
    std::cout << "nombre de solutions avt : " << solutions.size() << std::endl;
    solutions = dawg->findWords(chevalet);
    //FIN DU SWITCH , quelle que soit la methode, on se retrouve ici avec un ensemble de string
    //Calcul du meilleur mot (d'abord, seulement avec les points des lettres, plus tard, on fera avec les bonus)
    std::cout << "nombre de solutions : " << solutions.size() << std::endl;
    return findBestWordFromSet(solutions);
}

void Player::playsFirstRound() {
    std::string letters = "";
    bundle->displayDebug();
    takeLetters(7);
    for (int i = 0; i < 7; ++i) {
        letters += rack[i];
    }
    std::cout << "mes lettres : " << letters << std::endl;
    std::string bestWord = searchBestWord(letters);
    Console::display(*gameboard);
    gameboard->putWord(bestWord, 7, 7, 0); // putWord("mot", abs, ord, direction)
    Console::display(*gameboard);
}

void Player::plays() {
    bundle->displayDebug();
    Console::display(*gameboard);
    takeLetters(7);

    //faire rechercher un mot, en fonction d'une place
    //trouver le meilleur mot en fonction des points des lettres uniquement
    //placer le mot

}