/*
 * File:   Bundle.h
 * Author: jeremy
 *
 * Created on 9 décembre 2014, 15:29
 */

#ifndef BUNDLE_H
#define	BUNDLE_H

#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

class Bundle {
public:
    Bundle();
    bool isEmpty();
    char takeLetter();
    void deleteLetter(char);
    void init();
    int getPointOfChar(char);
    void displayDebug();
private:
    std::vector<char> letters;
    std::map<char, int> pointOfChar;
};



#endif	/* BUNDLE_H */

