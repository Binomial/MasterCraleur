/* 
 * File:   Main.cpp
 * Author: jeremy
 *
 * Created on 22 novembre 2014, 14:10
 */

#include <cstdlib>
#include "header/controller/anagramstring/Permut.h"
#include "header/controller/dawg/Trie.h"
#include "header/controller/anagramint/Dictionnary.h"
#include "header/controller/anagramint/FindWord.h"
#include "header/model/Bundle.h"
#include "header/model/GameBoard.h"
#include "header/view/Console.h"

using namespace std;

void testAnagramString(string letters) {
    Permut p;
    p.importDictionnary();
    p.generateWodWithWhite(letters);
    p.printSolution();
    //p.saveSol(letters);
}

void testAnagramInt(string letters) {
    Dictionnary dict;
    dict.importDictionnary();

    FindWord fw(dict.getMap());
    fw.permut(letters);
    fw.displaySolution();
}

void testDawg(string letters) {
    Trie* dawg = new Trie();
    dawg->loadDawg("./dict/dictFrDawg.dc");
    dawg->findWords(letters);
}

void testBundle() {
    Bundle *b = new Bundle();

    s_letter ll;

    b->initBundle();

    ll = b->takeLetter();
    cout << ll.car << " pts : " << ll.point << endl;

}

/*
 * 
 */
int main() {
    int choice;
    string letters;
    do {
        cout << endl << endl << "------ MENU ------" << endl << endl;
        cout << "0 - Exit" << endl << "1 - Anagram Int" << endl << "2 - Anagram String" << endl << "3 - DAWG" << endl << endl;
        cin >> choice;
    } while (choice < 0 || choice > 4);

    if (choice == 0) {
        cout << "Goodbye marylou" << endl;
    } else {

        switch (choice) {
            case 1:
                cout << "Vos lettres : ";
                cin >> letters;
                testAnagramInt(letters);
                break;
            case 2:
                cout << "Vos lettres : ";
                cin >> letters;
                testAnagramString(letters);
                break;
            case 3:
                cout << "Vos lettres : ";
                cin >> letters;
                testDawg(letters);
                break;
            case 4:
                Console *c = new Console();
                GameBoard *gb = new GameBoard();
                gb->initGameBoard();
                c->display(*gb);
                break;

        }
    }
    
    return 0;
}

