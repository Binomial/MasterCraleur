/* 
 * File:   Permut.h
 * Author: jeremy
 *
 * Created on 22 novembre 2014, 14:05
 */

#ifndef PERMUT_H
#define	PERMUT_H

#include <cstdio>
#include <string>
#include <fstream>
#include <set>
#include <map>
#include <algorithm> 
#include <iostream>
#include <sstream>

using namespace std;

class Permut {
public : 
    static bool next_rec(int n, int k, int *i, int j);
    static bool next(int n, int k, int *i);
    void calcul(string letters);
    void printSolution();
    void findAnagrams(string key);
    void lineToMap(string line);
    void importDictionnary();
    int nbWhite(string letters);
    void generateWodWithWhite(string letters);
    void saveSol();
private :
    set<string> setCombinaison;
    set<string> setSolution;
    map<string, set<string>> mapDict;
};

#endif	/* PERMUT_H */

