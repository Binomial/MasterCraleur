/*
 * File:   Bundle.h
 * Author: jeremy
 *
 * Created on 9 décembre 2014, 15:29
 */

#ifndef BUNDLE_H
#define	BUNDLE_H

#include <vector>
#include <algorithm>
#include <iostream>

class Bundle {
public:
    Bundle();
    bool isEmpty();
    char takeLetter();
    void init();

    void debug();
private:
    std::vector<char> letters;
};



#endif	/* BUNDLE_H */

