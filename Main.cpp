/* 
 * File:   Main.cpp
 * Author: jeremy
 *
 * Created on 22 novembre 2014, 14:10
 */

#include <cstdlib>
#include "header/anagramstring/Permut.h"
#include "header/dawg/Trie.h"
#include "header/anagramint/Dictionnary.h"
#include "header/anagramint/FindWord.h"

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
/*
 * 
 */
int main() {
    int choice;
    string letters;
    do{
        cout << endl << endl << "------ MENU ------" << endl<< endl;
        cout << "0 - Exit" << endl  << "1 - Anagram Int" << endl << "2 - Anagram String" << endl << "3 - DAWG" << endl << endl;
        cin >> choice;
    }while(choice < 0 || choice > 3);
    
    if(choice == 0) {
        cout << "Goodbye marylou" << endl;
    } else {
        
        cout << "Vos lettres : ";
        cin >> letters;
        
        switch(choice) {
            case 1:
                testAnagramInt(letters);
                break;
            case 2:
                testAnagramString(letters);
                break;
            case 3:
                testDawg(letters);
                break;
                        
        }
    }
    return 0;
}

