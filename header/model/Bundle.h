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


typedef struct {
    char car;
    int point;
}s_letter; 


class Bundle {
public :
    Bundle();
    bool isEmpty();
    s_letter takeLetter();
    void initBundle();
private :
    std::vector<s_letter> letters;
};



#endif	/* BUNDLE_H */

