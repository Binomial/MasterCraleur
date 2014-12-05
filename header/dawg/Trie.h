/* 
 * File:   Trie.h
 * Author: g
 *
 * Created on November 14, 2014, 8:30 PM
 */

#ifndef TRIE_H
#define	TRIE_H

#include <fstream>
#include <iostream>
#include <queue>
#include <cstdlib>
#include "Node.h"


class Trie{
public:
    Trie();
    Trie(Node*);
    
    /* Getters */
    int         getNumberOfNodes() const;  
        
    /* Public methods */
    void        deleteVect(Node*, std::vector<Node*>&);
    void        insertWord(std::string);
    void        minimize(Node*, std::vector<Node*>, Node*);
    void        minimize();
    bool        searchWord(std::string);
    std::string toGraphvizFormat();
    void        renumbering();
    std::string storeDawg();
    void        loadDawg(std::string);
    void        buildDawgAndStore(std::string, std::string);
    void        findWords(std::string);
    void        findWords(Node*, std::string, std::string);

    
private:
    Node* head;
    int number_of_nodes;
    std::vector<Node*> unchecked_leaf_nodes;
};

#endif	/* TRIE_H */

