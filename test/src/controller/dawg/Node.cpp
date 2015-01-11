#include "../../../header/controller/dawg/Node.h"


/*******************/
/*  Constr-Destr   */

/*******************/

Node::Node(int n) {
    num = n;
    color = 0;
    terminal = false;
}

Node::Node(int n, Node* ptr_father) {
    num = n;
    color = 0;
    terminal = false;
    fathers.push_back(ptr_father);
}


/*******************/
/*     Getters     */

/*******************/

int Node::getNum() const {
    return num;
}

int Node::getColor() const {
    return color;
}

Node* Node::getFather() {
    return fathers[0];
}

std::vector<Node*> Node::getFathers() const {
    return fathers;
}

t_map_of_edges Node::getEdges() const {
    return edges;
}

char Node::getLetterByChild(Node* ptr_child) {
    for (const auto& edge : edges) {
        if (edge.second->getNum() == ptr_child->getNum()) {
            return edge.first;
        }
    }
    return ' ';
}



/*******************/
/*     Setters     */

/*******************/

void Node::setNum(int n) {
    num = n;
}

void Node::setTerminal() {
    terminal = true;
}

void Node::setColor(int col) {
    color = col;
}



/*******************/
/* Public Methods  */

/*******************/

bool Node::isTerminal() {
    return terminal;
}

Node* Node::findChild(char letter) {
    t_map_of_edges::iterator it = edges.find(letter);
    if (it == edges.end()) {
        return nullptr;
    } else {
        return it->second;
    }
}

void Node::appendEdge(char letter, Node* ptr_node) {
    edges.insert(std::pair<char, Node*>(letter, ptr_node));
}

void Node::deleteEdge(char c) {
    edges.erase(c);
}

void Node::deleteNode(Node* ptr_node, Node* father, char letter, std::vector<Node*> &unchecked) {
    //On ne peut supprimer un noeud que s'il n'a qu'un pere.
    if (ptr_node->getFathers().size() <= 1) {
        ptr_node->deleteEdges(unchecked); //les fils deja suppr, reste que les pointeurs
        father->deleteEdge(letter);
        //-1 car on ne veut pas suppr le dernier qui sera pop
        for (std::size_t i = 0; i < unchecked.size() - 1; ++i) {
            if (unchecked.at(i) == ptr_node) {
                unchecked.erase(unchecked.begin() + i);
                break;
            }
        }
    }// delete ptr_node;  /*fait tout planter*/
}

void Node::deleteEdges(std::vector<Node*> &unchecked) {
    for (const auto& edge : edges) {
        deleteNode(edge.second, this, edge.first, unchecked);
    }
    edges.clear();
}

void Node::appendFather(Node* ptr_node) {
    fathers.push_back(ptr_node);
}

void Node::deleteLastFather() {
    fathers.pop_back();
}

bool Node::isEquivalentNode(Node nod) {
    Node* tmp;
    if (isTerminal() == nod.isTerminal()) {
        if (getEdges().size() == nod.getEdges().size()) {
            if (getEdges().size() == 0) {
                return true;
            } else {
                for (const auto& edge : getEdges()) {
                    //pour chq arete du noeud1, il doit avoir son equivalent
                    //pour l'arrete de meme lettre sur le noeud 2
                    tmp = nod.getEdges()[edge.first];
                    if (tmp == nullptr) {
                        return false;
                    }
                    if (!edge.second->isEquivalentNode(*(nod.getEdges()[edge.first]))) {
                        return false;
                    }
                }
                return true;
            }
        }
    }
    return false;
}

Node* Node::hasEquivalentNode(std::vector<Node*> nodes) {
    for (const auto& ptr_node : nodes) {
        if (isEquivalentNode(*ptr_node))
            return ptr_node;
    }
    return nullptr;
}