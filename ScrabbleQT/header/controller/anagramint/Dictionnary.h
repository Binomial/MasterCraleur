/* 
 * File:   Dictionnary.h
 * Author: jeremy
 *
 * Created on 14 novembre 2014, 22:17
 */

#ifndef DICTIONNARY_H
#define	DICTIONNARY_H

#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include<algorithm>

using namespace std;

class Dictionnary {
public : 
    
    void createDictionnary();
    // Create a dictionnary for the solution with map<string, set<string>>
    void createDictionnary2();
    void mapToFile();
    // Return the map
    map<string,set<string>> getMap();
    // insert a line in mapDict
    void lineToMap(string line);
    // Print the map
    void printMap();
    // Sort a word in alphabetic order
    string sortWord(string word);
    // read a dictionnary, and stock it on mapDict
    void importDictionnary();
    
    
private :
    map<string, set<string>> mapDict;
    string path;
};

#endif	/* DICTIONNARY_H */

