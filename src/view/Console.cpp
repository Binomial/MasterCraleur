
#include "../../header/view/Console.h"

void Console::display(GameBoard gb) {
    std::string separator;
    separator = "  ";
    std::cout << "AFFFICHAAAAGE" << std::endl;
    for(int x = 0; x < 15; x++) {
        for(int y = 0; y < 15; y++) {
            if(gb.getLetter(x,y).car == ' ' && gb.getCoef(x, y) != 0) {
                std::cout << gb.getCoef(x,y) << separator;
            } else {
                std::cout << gb.getLetter(x, y).car << separator;
            }
        }
        std::cout << std::endl;
    }
    std::cout << "FIN D'AFFFICHAAAAGE" << std::endl;
}
