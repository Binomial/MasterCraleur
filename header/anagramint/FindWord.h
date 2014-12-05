/* 
 * File:   FindWord.h
 * Author: jeremy
 *
 * Created on 14 novembre 2014, 23:04
 */

#ifndef FINDWORD_H
#define	FINDWORD_H

#include <string>
#include <cstdlib>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

class FindWord {
public:

    FindWord(map<string, set<string>> mapAn) : mapAn(mapAn) {
    }
    
    
    int nbWhite(string letters);
    void findWord(string letters);
    void permut(string letter);
    void findAll(string letter);
    void displaySolution();
private:
    map <string, set<string>> mapAn;
    set<string> solution;
};

#endif	/* FINDWORD_H */

