
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
