
#include "../../header/model/Bundle.h"

Bundle::Bundle() {
    letters.push_back('8');
    letters.push_back('8');

    for (int i = 0; i < 9; i++)
        letters.push_back('a');
    for (int i = 0; i < 15; i++)
        letters.push_back('e');
    for (int j = 0; j < 8; j++)
        letters.push_back('i');
    for (int i = 0; i < 6; i++)
        letters.push_back('n');
    for (int i = 0; i < 6; i++)
        letters.push_back('o');
    for (int i = 0; i < 6; i++)
        letters.push_back('r');
    for (int i = 0; i < 6; i++)
        letters.push_back('s');
    for (int i = 0; i < 6; i++)
        letters.push_back('t');
    for (int i = 0; i < 6; i++)
        letters.push_back('u');
    for (int i = 0; i < 5; i++)
        letters.push_back('l');
    for (int i = 0; i < 3; i++)
        letters.push_back('o');
    for (int i = 0; i < 3; i++)
        letters.push_back('d');
    for (int i = 0; i < 3; i++)
        letters.push_back('m');
    for (int i = 0; i < 2; i++)
        letters.push_back('g');
    for (int i = 0; i < 2; i++)
        letters.push_back('b');
    for (int i = 0; i < 2; i++)
        letters.push_back('c');
    for (int i = 0; i < 2; i++)
        letters.push_back('p');
    for (int i = 0; i < 2; i++)
        letters.push_back('f');
    for (int i = 0; i < 2; i++)
        letters.push_back('h');
    for (int i = 0; i < 2; i++)
        letters.push_back('v');

    letters.push_back('j');
    letters.push_back('q');
    letters.push_back('k');
    letters.push_back('w');
    letters.push_back('x');
    letters.push_back('y');
    letters.push_back('z');
}

void Bundle::init() {
    std::random_shuffle(letters.begin(), letters.end());
}

bool Bundle::isEmpty() {
    return letters.empty();
}

char Bundle::takeLetter() {
    char result = letters.at(letters.size() - 1);
    letters.pop_back();
    return result;
}

void Bundle::displayDebug() {
    for (int i = 0; i < letters.size(); ++i) {
        std::cout << letters[i] << " ";
    }
    std::cout << std::endl;
}

