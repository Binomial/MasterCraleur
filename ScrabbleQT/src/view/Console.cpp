
#include "../../header/view/Console.h"

void Console::display(GameBoard gb) {
    std::string separator;
    bool isAnchor = false;
    separator = "  ";
    std::cout << "Plateau :" << std::endl;
    for (int y = 0; y < 15; y++) {
        for (int x = 0; x < 15; x++) {
            isAnchor = false;
            for (auto const& anchor : gb.getAnchors()) {
                if (x == anchor.second.abs && y == anchor.second.ord) {
                    isAnchor = true;
                    break;
                }
            }
            if (isAnchor) {
                std::cout << "%" << separator;
            } else {
                if (gb.getLetter(x, y) == ' ' && gb.getCoef(x, y) != 0) {
                    std::cout << gb.getCoef(x, y) << separator;
                } else if (gb.getLetter(x, y) == ' ') {
                    std::cout << "." << separator;
                } else {
                    std::cout << gb.getLetter(x, y) << separator;
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Console::startGame(Player player) {
    int step = 0;
    std::map<int, s_solution> solutions;
    while (step < 5) {
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "#Tour de jeu numéro " << step << std::endl;
        std::cout << std::endl;

        solutions = player.plays(0); //int : methode choisie
        for (std::size_t i = 0; i < solutions.size(); ++i) {
            std::cout << i << ": " << solutions[i].word << " (" << solutions[i].abs << "," << solutions[i].ord << ") d" << solutions[i].dir << std::endl;
        }
        /* Etape 4 : Choix d'un mot */

        int num = 0;


        std::cout << "Choisir mot a placer" << std::endl;
        std::cin >> num;

        /* Etape 4 : Placement du mot */
        player.putWord(solutions[num].word, solutions[num].abs, solutions[num].ord, solutions[num].dir); // putWord("mot", abs, ord, direction)
        step++;

        player.upDate(solutions[num], true);

        display(player.getGameBoard());

    }
}