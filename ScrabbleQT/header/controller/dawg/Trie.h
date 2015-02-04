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

typedef struct {
    std::string word;
    int abs;
    int ord;
    int dir;
    int points;
} s_solution;

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
    std::vector<s_solution> findWords(std::string, GameBoard, s_pos);
    void findWords(Node*, std::string, std::string);
    void extendRight(std::string partialWord, std::string chevalet, GameBoard, Node* head, s_pos anchor, int);
    void leftPart(std::string, std::string, GameBoard, Node*, s_pos, int, int);
    bool isCorrect(GameBoard, int, int, char, int);
    bool isCorrectPrefix(GameBoard, std::string, s_pos, int);
    bool isConnected(GameBoard, int, int);
    int countPoints(s_solution, GameBoard);
private:
    Node* head;
    int number_of_nodes;
    std::vector<s_solution> vectSolutions;
    std::vector<Node*> unchecked_leaf_nodes;
};

#endif	/* TRIE_H */

