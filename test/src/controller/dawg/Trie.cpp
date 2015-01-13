#include <locale>
#include "../../../header/controller/dawg/Trie.h"

/* METHODES DE CONSTRUCTION DU DICTIONNAIRE */

Trie::Trie() {
    head = new Node(0, NULL);
    number_of_nodes = 0;
}

Trie::Trie(Node* in_head) {
    head = in_head;
    number_of_nodes = 0;
}

int Trie::getNumberOfNodes() const {
    return number_of_nodes + 1;
}

void Trie::insertWord(std::string word) {
    Node* ptr_current_node = head;
    Node* ptr_next_node;
    for (unsigned int i = 0; i < word.length(); i++) {
        ptr_next_node = ptr_current_node->findChild(word[i]);
        if (ptr_next_node != nullptr) {
            if (ptr_next_node->isTerminal())
                deleteVect(ptr_next_node, unchecked_leaf_nodes);
            ptr_current_node = ptr_next_node;
        } else {
            number_of_nodes++;
            Node* ptr_new_node = new Node(number_of_nodes, ptr_current_node);
            ptr_current_node->appendEdge(word[i], ptr_new_node);
            ptr_current_node = ptr_new_node;
        }
    }
    ptr_current_node->setTerminal();
    unchecked_leaf_nodes.push_back(ptr_current_node);
}

void Trie::minimize() {
    while (!unchecked_leaf_nodes.empty()) {
        minimize(unchecked_leaf_nodes.back(), unchecked_leaf_nodes, nullptr);
        unchecked_leaf_nodes.pop_back();
    }
}

void Trie::minimize(Node* ptr_node, std::vector<Node*> unchecked_nodes, Node* save_eq_node) {
    Node* eq_node;
    Node* father;
    //Recherche de noeud équivalent
    eq_node = ptr_node->hasEquivalentNode(unchecked_nodes);
    //Un noeud a été trouvé
    if (eq_node != nullptr && eq_node != ptr_node && eq_node != head) {
        number_of_nodes--;
        // le pere du noeud courant : father
        father = ptr_node->getFather();
        //la lett
        //char letter = (ptr_node->getEdges().begin())->first;
        char father_letter = father->getLetterByChild(ptr_node);
        if (father_letter > 'z' || father_letter < 'a') {
            std::cerr << "minimize() FAILED" << std::endl;
            exit(3);
        } else {
            Node::deleteNode(ptr_node, father, father_letter, unchecked_leaf_nodes);
            if (save_eq_node != nullptr) {
                //Le noeud equivalent precedent
                save_eq_node->deleteLastFather();
            }
            unchecked_nodes = eq_node->getFathers();
            father->appendEdge(father_letter, eq_node); //PB : map... si la lettre existe deja...
            eq_node->appendFather(father);
            ptr_node = father;
            father = (ptr_node->getFather() == nullptr) ? head : father->getFather();
            save_eq_node = eq_node;
            minimize(ptr_node, unchecked_nodes, save_eq_node);
        }
    }
}

void Trie::deleteVect(Node* ptr_node, std::vector<Node*> &vect) {
    if (vect.back() == ptr_node) {
        vect.pop_back();
    }
}

void Trie::renumbering() {
    Node* p_current_node;
    std::queue<Node*> queue;
    queue.push(head);
    head->setColor(1);
    int num = 0;
    head->setColor(num);
    while (!queue.empty()) {
        p_current_node = queue.front();
        queue.pop();
        for (auto& edge : p_current_node->getEdges()) {
            if (edge.second->getColor() == 0) {
                num++;
                edge.second->setNum(num);
                edge.second->setColor(1);
                queue.push(edge.second);
            }
        }
    }
    number_of_nodes = num;
}

std::string Trie::storeDawg() {
    Node* p_current_node;
    std::queue<Node*> queue;
    queue.push(head);
    head->setColor(0);
    std::string color = "";
    std::string result = "";
    std::string num = "";
    result = std::to_string(number_of_nodes + 1) + "\n";
    while (!queue.empty()) {
        p_current_node = queue.front();
        queue.pop();

        for (auto& edge : p_current_node->getEdges()) {
            num = std::to_string((edge.second)->getNum());

            result += num + edge.first;
            if ((edge.second)->isTerminal()) {
                result += "#-";
            } else
                result += "-";
            if (edge.second->getColor() == 1) {
                edge.second->setColor(0);
                queue.push(edge.second);
            }

        }
        result += "\n";
    }

    return result;
}

std::string Trie::toGraphvizFormat() {
    Node* p_current_node;
    std::queue<Node*> queue;
    queue.push(head);
    head->setColor(1);
    std::string header = "digraph G {\n";
    std::string color = "";
    std::string body = "";
    std::string num = "";

    while (!queue.empty()) {
        p_current_node = queue.front();
        queue.pop();

        for (auto& edge : p_current_node->getEdges()) {

            num = std::to_string((edge.second)->getNum());
            if ((edge.second)->isTerminal()) {
                color += num + " [shape=doublecircle]\n";
            }
            body += std::to_string(p_current_node->getNum()) + "->" + num
                    + " [label = " + edge.first + "];\n";
            if (edge.second->getColor() == 0) {
                edge.second->setColor(1);
                queue.push(edge.second);
            }

        }
    }

    return header + color + body + "}";
}

void Trie::loadDawg(std::string path) {
    std::ifstream dawg(path.c_str(), std::ios::in);
    if (dawg) {
        std::string line;
        std::string num_str = "";
        Node* ptr_node;
        char letter;
        int num_current_node = 0;
        std::vector<Node*> nodes;
        //1ere ligne : nombre de noeuds
        getline(dawg, line);
        int i_max = std::stoi(line) + 1;
        //creation de tous les noeuds avec leur num.
        nodes.push_back(head);
        for (int i = 1; i < i_max; ++i) {
            ptr_node = new Node(i);
            nodes.push_back(ptr_node);
        }
        //Creation des liens entre les noeuds
        while (getline(dawg, line)) {
            ptr_node = nodes[num_current_node];
            for (unsigned int i = 0; i < line.length(); ++i) {
                if (line[i] >= '0' && line[i] <= '9') {
                    num_str += line[i];
                } else {
                    //il y a deja eu un numero
                    if (num_str.length() > 0) {
                        if ('a' <= line[i] && line[i] <= 'z') {
                            letter = line[i];
                        } else {
                            if (line[i] == '-') {
                                nodes[num_current_node]->appendEdge(letter, nodes[std::stoi(num_str)]);
                                if (line[i - 1] == '#') {
                                    nodes[std::stoi(num_str)]->setTerminal();
                                }
                                num_str = "";
                            }
                        }
                    }
                }
            }
            num_str = "";
            num_current_node++;
        }
        number_of_nodes = num_current_node;
        dawg.close();
        // std::cout << "Dictionnaire chargé" << std::endl;
    }
    //else std::cerr << "Erreur d'ouverture du dictionnaire" << std::endl;
}

void Trie::buildDawgAndStore(std::string pathDicoText, std::string pathResult) {
    std::ifstream dicoText(pathDicoText.c_str(), std::ios::in);
    std::ofstream result(pathResult.c_str(), std::ios::out | std::ios::trunc);
    if (dicoText) {
        std::string word;
        //std::cout << "Dictionnaire ouvert" << std::endl;
        while (getline(dicoText, word)) {
            insertWord(word);
        }
        dicoText.close();
        //std::cout << "Dictionnaire fermé" << std::endl;
        //std::cout << "Compression." << std::endl;
        minimize();
        //std::cout << "Renumérotation." << std::endl;
        renumbering();
        //std::cout << "Enregistrement du Dawg." << std::endl;
        if (result) {
            result << storeDawg();
            result.close();
        }
    } else {
        std::cerr << "Erreur ouverture fichier";
    }
}



/* * * * * * * * * * * * * * * * *
 * METHODES DE RECHERCHE DE MOTS *
 * * * * * * * * * * * * * * * * */

//"word" est-il dans le dictionnaire ?

bool Trie::searchWord(std::string word) {
    Node* tmp_node;
    Node* p_current_node = head;
    while (p_current_node != nullptr) {
        for (unsigned int i = 0; i < word.length(); i++) {
            tmp_node = p_current_node->findChild(word[i]);
            if (tmp_node == nullptr) {
                return false;
            }
            p_current_node = tmp_node;
        }
        if (p_current_node->isTerminal()) {
            return true;
        }
        return false;
    }
    return false;
}


//Vérifie qu'une nouvelle lettre posée forment des mots corrects Verticalement

bool Trie::isCorrect(GameBoard gb, int abs, int ord, char l, int dir) {
    if (dir == 0) { // Mot horizontal
        if (gb.isFreeCase(abs, ord - 1) && gb.isFreeCase(abs, ord + 1)) {
            return true;
        } else {
            std::string newWord = "";
            newWord += l;
            int y = ord - 1;
            while (y >= 0 && !gb.isFreeCase(abs, y)) {
                newWord = gb.getLetter(abs, y) + newWord;
                y--;
            }
            y = ord + 1;
            while (y < 15 && !gb.isFreeCase(abs, y)) {
                newWord += gb.getLetter(abs, y);
                y++;
            }

            return searchWord(newWord);
        }

    } else { //Mot Vertical
        if (gb.isFreeCase(abs - 1, ord) && gb.isFreeCase(abs + 1, ord)) {
            return true;
        } else {

            std::string newWord = "";
            newWord += l;
            int x = abs - 1;
            while (x >= 0 && !gb.isFreeCase(x, ord)) {
                newWord = gb.getLetter(x, ord) + newWord;
                x--;
            }
            x = abs + 1;
            while (x < 15 && !gb.isFreeCase(x, ord)) {
                newWord += gb.getLetter(x, ord);
                x++;
            }
            return searchWord(newWord);
        }
    }
}

bool Trie::isCorrectPrefix(GameBoard gb, std::string word, s_pos anchor, int dir) {
    if (dir == 0) {
        for (std::size_t i = 0; i < word.length(); ++i) {
            if (!isCorrect(gb, anchor.abs - word.length() + i, anchor.ord, word[i], dir)) {
                return false;
            }
        }
    }
    if (dir == 1) {
        for (std::size_t i = 0; i < word.length(); ++i) {
            if (!isCorrect(gb, anchor.abs, anchor.ord - word.length() + i, word[i], dir)) {
                return false;
            }
        }
    }
    return true;
}

bool Trie::isConnected(GameBoard gb, int abs, int ord) {

    return (!gb.isFreeCase(abs - 1, ord) || !gb.isFreeCase(abs, ord - 1));
}

// Trouver les mots a partir de lettres, d'un plateau, et d'une position

std::vector<s_solution> Trie::findWords(std::string chevalet, GameBoard gb, s_pos anchor) {
    std::size_t joker1_pos, joker2_pos;
    int limit = 0;

    joker1_pos = chevalet.find('8', 0);
    if (joker1_pos != std::string::npos) { //s'il y a des jokers
        joker2_pos = chevalet.find('8', joker1_pos + 1);
        if (joker2_pos != std::string::npos) {
            for (char c1 = 'a'; c1 <= 'z'; ++c1) {
                chevalet[joker1_pos] = c1;
                for (char c2 = c1; c2 <= 'z'; ++c2) {
                    chevalet[joker2_pos] = c2;
                    findWords(chevalet, gb, anchor);
                }
            }
        } else {
            for (char c = 'a'; c <= 'z'; ++c) {
                chevalet[joker1_pos] = c;
                findWords(chevalet, gb, anchor);
            }
        }
    }//une fois les jokers remplacés
        //else findWords(head, chevalet, "");
    else {
        //on compte la longueur max du prefix
        int abs = anchor.abs - 1;
        while (gb.isFreeCase(abs, anchor.ord) && abs > 0) {
            abs--;
            limit++;
        }
        //std::cout << "APPEL DE LEFTPART, avec limit=" << limit << std::endl;
        leftPart("", chevalet, gb, head, anchor, limit, 0);
        //MOTS VERTICAUX
        int ord = anchor.ord - 1;
        limit = 0;
        while (gb.isFreeCase(anchor.abs, ord) && ord > 0) {
            ord--;
            limit++;
        }
        leftPart("", chevalet, gb, head, anchor, limit, 1);
    }
    return vectSolutions;
}

/*ATTENTION : version pour mot horiozntal*/

/* ExtendRight(PartialWord, node N, case a droite de l'ancre){*/
void Trie::extendRight(std::string partialWord, std::string chevalet, GameBoard gb, Node* node, s_pos rsquare, int dir) {
    if (isCorrectPrefix(gb, partialWord, rsquare, dir)) {//on ne cherche que si le prefixe est correct ds le plateau
        //Cas ou pas de prefixe et ancre a la fin d'un mot (pas de connectivité)
        if (partialWord != "" || isConnected(gb, rsquare.abs, rsquare.ord)) {
            s_pos next_square;
            Node* p_new_node = nullptr;
            std::string new_partialWord;

            if (gb.isFreeCase(rsquare.abs, rsquare.ord) && rsquare.abs < 15 && chevalet.length() > 0) {
                //std::cout << "(" << rsquare.abs << "," << rsquare.ord << ") IS FREE" << std::endl;
                if (node->isTerminal()) {
                    s_solution sol;
                    sol.word = partialWord;
                    sol.dir = dir;
                    if (dir == 0) {
                        sol.abs = rsquare.abs - partialWord.length();
                        sol.ord = rsquare.ord;
                    } else {
                        sol.abs = rsquare.abs;
                        sol.ord = rsquare.ord - partialWord.length();
                    }
                    vectSolutions.push_back(sol);
                }
                for (unsigned int i = 0; i < chevalet.length(); ++i) {
                    p_new_node = node->findChild(chevalet[i]);
                    if (p_new_node != nullptr) {//un mot existe étendu par la lettre du chevalet
                        if (isCorrect(gb, rsquare.abs, rsquare.ord, chevalet[i], dir)) {//si de nouveaux mots sont formés et qu'ils existent
                            //retirer la lettre du chevalet
                            std::string save_chevalet = chevalet;
                            new_partialWord = partialWord + chevalet[i];
                            chevalet.erase(i, 1);

                            next_square = rsquare;
                            (dir == 0) ? next_square.abs++ : next_square.ord++;

                            extendRight(new_partialWord, chevalet, gb, p_new_node, next_square, dir);
                            //remettre ds le chevalet
                            chevalet = save_chevalet;
                        }
                    }
                }
            } else {
                char l = gb.getLetter(rsquare.abs, rsquare.ord);
                p_new_node = node->findChild(l);
                if (p_new_node != nullptr) {

                    next_square = rsquare;
                    (dir == 0) ? next_square.abs++ : next_square.ord++;
                    new_partialWord = partialWord + l;
                    extendRight(new_partialWord, chevalet, gb, p_new_node, next_square, dir);
                }
            }
        }
    }
}

void Trie::leftPart(std::string partialWord, std::string chevalet, GameBoard gb, Node* node, s_pos anchor, int limit, int dir) {
    s_pos rsquare = anchor;
    std::string new_partialWord;
    Node* p_new_node = nullptr;
    (dir == 0) ? rsquare.abs++ : rsquare.ord++;
    extendRight(partialWord, chevalet, gb, node, rsquare, dir);
    if (limit > 0) {
        for (unsigned int i = 0; i < chevalet.length(); ++i) {
            //std::cout << "Lettre étudiée " << chevalet[i] << std::endl;
            p_new_node = node->findChild(chevalet[i]);
            if (p_new_node != nullptr) {


                //retirer la lettre du chevalet
                std::string save_chevalet = chevalet;
                new_partialWord = partialWord + chevalet[i];
                chevalet.erase(i, 1);

                leftPart(new_partialWord, chevalet, gb, p_new_node, anchor, limit - 1, dir);

                //remettre ds le chevalet
                chevalet = save_chevalet;
            }
        }
    }
}
