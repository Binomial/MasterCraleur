#include "../../header/anagramint/Dictionnary.h"
#include "../../header/anagramint/FindWord.h"

using namespace std;

int FindWord::nbWhite(string letters) {
    int nbWhiteLetters = 0;
    for (int i = 0; i < 3; i++) {
        if (letters[i] == '8') {
            nbWhiteLetters++;
        }
    }
    return nbWhiteLetters;
}

void FindWord::findWord(string key) {
    if (mapAn.count(key) > 0) {
        cout << "youpi" << endl;
        //La clé existe, on affiche les solutions
        for (const auto& word : mapAn[key]) {
            cout << word << " ";
            solution.insert(word);
        }
    } else {
        cout << "chiotte pour la cle " << key << endl;
        // La cle n'existe pas
    }

}

// créer toutes les clés de letter de la taille de letter
void FindWord::permut(string letter) {
    solution.clear();
    string s = letter;
    sort(s.begin(), s.end());
    findAll(s);
    
    while (next_permutation(s.begin(), s.end())) {
        findAll(s);
    }
}

// Découpe letter de 2 à taille de letter, et trouve les anagrammes
void FindWord::findAll(string letter) {
    for (int i = 2; i < letter.length()+1; i++) {
        string tmp = letter;
        tmp.resize(i);
        findWord(tmp);
    }
}

void FindWord::displaySolution() {
    cout << "Avec vos lettres, vous pouvez faire :" << endl;
 
    for(const auto& word : solution) {
        cout << word << endl;
    }
}
