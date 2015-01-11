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
#include <set>
#include <cstdlib>
#include "Node.h"
#include "../../model/GameBoard.h"

class Trie {
public:
    Trie();
    Trie(Node*);

    /* Getters */
    int getNumberOfNodes() const;

    /* Public methods */
    void deleteVect(Node*, std::vector<Node*>&);
    void insertWord(std::string);
    void minimize(Node*, std::vector<Node*>, Node*);
    void minimize();
    bool searchWord(std::string);
    std::string toGraphvizFormat();
    void renumbering();
    std::string storeDawg();
    void loadDawg(std::string);
    void buildDawgAndStore(std::string, std::string);
    //methodes Trie+Plateau
    std::set<std::string> findWords(std::string, GameBoard, s_pos);
    void findWords(Node*, std::string, std::string);
    void extendRight(std::string partialWord, std::string chevalet, GameBoard, Node* head, s_pos anchor);
    void leftPart(std::string, std::string, GameBoard, Node*, s_pos, int);
    bool isCorrect(GameBoard, int, int, char);
    bool isCorrectPrefix(GameBoard, std::string, s_pos);
private:
    Node* head;
    int number_of_nodes;
    std::set<std::string> setSolutions;
    std::vector<Node*> unchecked_leaf_nodes;
};

#endif	/* TRIE_H */

