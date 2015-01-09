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
    numberOfLettersOnRack = 7;
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
    //changer 7
    for (int i = 0; i < 7; i++) {
        result += rack[i];
    }
    return result;
}


/* DEPRECATED : fonction inutile, ce sera a l'utilisateur de choisir le mot de son choix a placer parmi la liste
   de mots proposés, avec la case ou les placer, la direction, et le nb de points*/
//std::string Player::findBestWordFromSet(std::set<std::string> solutions) {
//    std::string bestWord = "";
//    int points;
//    int bestPoints = 0;
//    // std::cout << "Debut du for" << std::endl;
//    for (const auto& word : solutions) {
//        points = 0;
//        //std::cout << word << std::endl;
//        for (int i = 0; i < word.length(); ++i) {
//            points += bundle->getPointOfChar(word[i]); // Pour l'sintant on tient pas compte des coeff bonus du plateau
//        }
//        if (points > bestPoints) {
//            bestPoints = points;
//            bestWord = word;
//        }
//    }
//    std::cout << "Meilleur mot = " << bestWord << "( " << bestPoints << ")" << std::endl;
//    return bestWord;
//}


/* J'ai modif la valeur de retour et le nom, on doit juste trouver l'ensemble des mots, calculer leurs points et proposer la liste*/
// ANCIENNEMENT : std::string Player::searchBestWord(std::string chevalet, int method) {

void Player::findWords(std::string chevalet, s_pos anchor, int method) {

    std::set<std::string> solutions;

    switch (method) {
        case 0:
            Trie *dawg = new Trie();

            dawg->loadDawg("dict/dictFrDawg.dc");
            solutions = dawg->findWords(chevalet, *gameboard, anchor);

            std::cout << "SOLUTIONS" << std::endl;
            for (auto const& sol : solutions) {
                std::cout << sol << std::endl;
            }
            break;
            //case 1: //anagramint
            //   break;
            //case 2: //anagramstring
            //   break;
    }
    //Calcul des points
    //TODO : fonction_calcule_points(solutions) -> renvoie une structure avec Mot, Position, Points
    //Afficher la liste des solutions
    //l'utilisateur choisit un mot
    //le mot est placé sur plateau et c'est reparti pour un tour.


}

void Player::plays() {

    std::string letters = "";
    s_pos currentAnchor;

    /*Affichages */
    bundle->displayDebug();
    //On remplit le chevalet
    takeLetters(7 - numberOfLettersOnRack);
    for (int i = 0; i < 7; ++i) {
        letters += rack[i];
    }

    std::cout << "Chevalet(" << numberOfLettersOnRack << ") : <" << letters << ">" << std::endl;
    std::cout << std::endl;
    std::cout << "Ancres(" << gameboard->getAnchors().size() << ") " << std::endl;
    std::cout << std::endl;
    Console::display(*gameboard);
    std::cout << std::endl;

    /* Recherche des mots */
    for (auto const& anchor : gameboard->getAnchors()) {
        findWords(letters, anchor.second, 0);
    }

    /* calcul des points*/
    //@TODO

    /* Choix d'un mot */
    std::string wordToPut = "";
    int abs = 0;
    int ord = 0;
    std::cout << "Choisir mot a placer" << std::endl;
    std::cin >> wordToPut;
    std::cout << "abs ?" << std::endl;
    std::cin >> abs;
    std::cout << "ord ?" << std::endl;
    std::cin >> ord;

    gameboard->putWord(wordToPut, abs, ord, 0); // putWord("mot", abs, ord, direction)

    /*Modif des ancres */
    s_pos begin;
    begin.abs = abs;
    begin.ord = ord;


    gameboard->upDateAnchors(begin, wordToPut.length(), 0);


    Console::display(*gameboard);

    /* Modif du chevalet */
    numberOfLettersOnRack = 7 - wordToPut.length();
    //retrait des lettres dans le chevalet
    for (int i = 0; i < 7; ++i) {
        std::size_t pos;
        pos = wordToPut.find(rack[i]);
        if (pos != std::string::npos) {
            rack[i] = ' ';
            wordToPut.erase(pos, 1);
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









    //    bool connection = false; // mot connecté a une lettre du plateau

    //    numberOfLettersOnRack = 7;
    //    for (int i = 0; i < numberOfLettersOnRack; ++i) {
    //        cst_letters += rack[i];
    //    }
    //    //ligne7
    //
    //    //x = case de depart du mot cherché
    //    for (int x = 0; x < 15; ++x) {
    //        letters = cst_letters;
    //        std::cout << "ETAPE " << x << " : case(H," << x + 1 << ")" << std::endl;
    //        int final_pos = x;
    //        for (int l = 0; l < 7; ++final_pos) {
    //            std::cout << "\t[Lettre du chevalet <" << final_pos + 1 << ">]" << std::endl;
    //            //depassement
    //            if (final_pos >= 15) {
    //                std::cout << "\t\t[Depassement]" << std::endl;
    //                break;
    //            }
    //            //si on rencontre une case occupee
    //            if (!gameboard->isFreeCase(7, final_pos)) {
    //                std::cout << "\t\t[Case occupee] " << gameboard->getLetter(7, final_pos) << std::endl;
    //                std::cout << "\t\t[Connectivité : OK]" << std::endl;
    //                connection = true;
    //                letters += gameboard->getLetter(7, final_pos);
    //            } else ++l;
    //        }
    //        std::cout << "\t[Chevalet étudié entre pos(" << x + 1 << ") et pos(" << final_pos + 1 << ")" << std::endl;
    //        if (!connection) {
    //            //aucune lettre n'a été croisée, on regarde la suivante
    //            //NB : normalement il faut regarder aussi une eventuelle connectivité en bas ou en haut etc.
    //
    //            if (!gameboard->isFreeCase(7, final_pos)) {
    //
    //                connection = true;
    //                while (!gameboard->isFreeCase(7, final_pos)) {
    //                    letters += gameboard->getLetter(7, final_pos);
    //                    final_pos++;
    //                }
    //                std::cout << "\t\t[Connectivité -> OK - Recherche de mot (" << letters << ") ]" << std::endl;
    //                //là, on peut chercher les mots, sinon c'est pas la peine
    //                result = searchBestWord(letters, 0);
    //            } else std::cout << "\t\t[Connectivité -> KO - Pas de recherche de mot]" << std::endl;
    //
    //        } else {
    //            std::cout << "\t[Recherche de mot (" << letters << ") ]" << std::endl;
    //            result = searchBestWord(letters, 0);
    //        }
    //        std::cout << "\tResultat à la place " << x << " : " << result << std::endl;
    //
    //        //trouver le meilleur mot en fonction des points des lettres uniquement
    //        //placer le mot
    //    }

}