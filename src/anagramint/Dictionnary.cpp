#include "../../header/anagramint/Dictionnary.h"

using namespace std;

map<string, set<string>> Dictionnary::getMap() {
    return mapDict;
}

void Dictionnary::printMap() {
    ofstream file("dico/new.dc", ios::out | ios::trunc);
    for (const auto& anagram : mapDict) {
        cout << anagram.first;
        for (const auto& set : mapDict[anagram.first]) {
            cout << " " << set;
        }
        cout << endl;
    }
}

string Dictionnary::sortWord(string word) {
    sort(word.begin(), word.end());
    return word;
}

void Dictionnary::mapToFile() {
    ofstream file("dico/dictFr2.dc", ios::out | ios::trunc);
    if (file) {
        for (const auto& anagram : mapDict) {
            file << anagram.first;
            for (const auto& set : mapDict[anagram.first]) {
                file << " " << set;
            }
            file << endl;
        }
        cout << "The map is save" << endl;
    } else {
        cerr << "Couldn't create the file" << endl;
    }
}

void Dictionnary::createDictionnary2() {
    ifstream file("dico/dicoFr.dc");

    if (file) {
        string line;

        while (getline(file, line)) {
            string temp = line;
            sort(temp.begin(), temp.end());
            mapDict[temp].insert(line);
        }
    } else {
        cerr << "Couldn't read the dictionnary" << endl;
    }
}

/*void Dictionnary::createDictionnary() {
    ofstream file("dico/new.dc");
    string temp = "";
    string wordsort;
    bool first = true;

    if (file) {
        for (const auto& anagram : mapDict) {
            for (const auto& set : mapDict[anagram.first]) {
                temp = temp + " " + set;
                if (first) {
                    wordsort = sortWord(set);
                    first = false;
                }
            }
            file << wordsort << temp << endl;
            first = true;
            temp = "";
        }
    } else {
        cerr << "Erreur" << endl;
    }
}
*/
void Dictionnary::lineToMap(string line) {
    string cle;
    int position = 0;
    unsigned int t = 0;
    string tmp;
    while (t <= line.length()) {
        if (line[t] == ' ' || t == line.length()) {
            position++;
            if (position == 1) {
                istringstream(tmp) >> cle;
            } else {
                mapDict[cle].insert(tmp);
            }
            tmp = "";
        } else {
            tmp += line[t];
        }
        t++;
    }
}

void Dictionnary::importDictionnary() {
    ifstream file("./dict/dictFrAnagramIntKey.dc", ios::in);

    if (file) {
        string line;
        while (getline(file, line)) {
            lineToMap(line);
        }
        cout << "the map was loaded" << endl;
        
    } else {
        cerr << "Can't open the dictionnary" << endl;
    }
}