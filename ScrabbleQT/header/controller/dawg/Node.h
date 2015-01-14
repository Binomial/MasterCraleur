/* 
 * File:   Node.h
 * Author: g
 *
 * Created on November 14, 2014, 8:31 PM
 */

#ifndef NODE_H
#define	NODE_H

#include <map>
#include <vector>
#include <iostream>
#include <iterator>


class Node {
    
public:
    
    Node(int n);
    Node(int, Node*);
    
    /* Getters */
    int getNum() const;
    int getColor() const;
    Node* getFather();
    std::vector<Node*> getFathers() const;
    std::map<char, Node*> getEdges() const;
    char getLetterByChild(Node*);
    
    /* Setters */
    void setNum(int);
    void setTerminal();
    void setColor(int);

    /* Public methods */
    bool isTerminal();
    Node* findChild(char);
    void appendEdge(char, Node*);
    void deleteEdge(char c);
    static void deleteNode(Node*, Node*, char, std::vector<Node*>&);
    void deleteEdges(std::vector<Node*>&);    
    void appendFather(Node*);
    void deleteLastFather();
    bool isEquivalentNode(Node);
    Node* hasEquivalentNode(std::vector<Node*>);

    
private:
    int num;
    int color;
    bool terminal;
    std::map<char,Node*> edges;
    std::vector<Node*> fathers;    
};

typedef std::map<char, Node*> t_map_of_edges; 


#endif	/* NODE_H */

