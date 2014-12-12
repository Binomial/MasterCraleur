#include <locale>
#include "../../../header/controller/dawg/Trie.h"


Trie::Trie() {
    head = new Node(0, NULL);
    number_of_nodes = 0;
}


Trie::Trie(Node* in_head){
    head = in_head;
    number_of_nodes = 0;
}


int Trie::getNumberOfNodes() const{
    return number_of_nodes+1;
}


void Trie::insertWord(std::string word) {    
    Node* ptr_current_node = head;
    Node* ptr_next_node;
    for (unsigned int i = 0; i < word.length(); i++) {   
        ptr_next_node = ptr_current_node->findChild( word[i] );
        if ( ptr_next_node != nullptr ) {  
            if ( ptr_next_node->isTerminal() )
                deleteVect(ptr_next_node, unchecked_leaf_nodes);
            ptr_current_node = ptr_next_node;         
        } 
        else {
            number_of_nodes++;
            Node* ptr_new_node = new Node( number_of_nodes , ptr_current_node );
            ptr_current_node->appendEdge( word[i], ptr_new_node );            
            ptr_current_node = ptr_new_node;           
        }
    }
    ptr_current_node->setTerminal();
    unchecked_leaf_nodes.push_back(ptr_current_node);
}
    
   
void Trie::minimize() {
    while(!unchecked_leaf_nodes.empty()){
        minimize(unchecked_leaf_nodes.back(), unchecked_leaf_nodes, nullptr);
        unchecked_leaf_nodes.pop_back();
    }
}
 
   
void Trie::minimize(Node* ptr_node, std::vector<Node*> unchecked_nodes, Node* save_eq_node ) {
    char letter;
    Node* eq_node;
    Node* father;
    //Recherche de noeud équivalent
    eq_node = ptr_node->hasEquivalentNode(unchecked_nodes);
    //Un noeud a été trouvé
    if(eq_node != nullptr && eq_node!=ptr_node && eq_node!=head){
        number_of_nodes--;
        // le pere du noeud courant : father
        father = ptr_node->getFather();
        //la lett
        letter = (ptr_node->getEdges().begin())->first; 
        char father_letter = father->getLetterByChild(ptr_node);
        if(father_letter>'z' || father_letter<'a'){
            std::cerr<<"minimize() FAILED"<<std::endl;
            exit(3);
        }
        else {
            Node::deleteNode(ptr_node, father, father_letter, unchecked_leaf_nodes);
            if(save_eq_node!=nullptr){
                    //Le noeud equivalent precedent
                    save_eq_node->deleteLastFather();
            }            
            unchecked_nodes = eq_node->getFathers();
            father->appendEdge(father_letter, eq_node);//PB : map... si la lettre existe deja...
            eq_node->appendFather(father);
            ptr_node = father;
            father = (ptr_node->getFather()==nullptr)?head:father->getFather();
            save_eq_node = eq_node;
            minimize(ptr_node, unchecked_nodes, save_eq_node);
        }
    }
}
    
    
bool Trie::searchWord(std::string word) {
    Node* tmp_node ; 
    Node* p_current_node = head;
    while(p_current_node != nullptr){
        for ( unsigned int i = 0; i < word.length(); i++ ){
            tmp_node = p_current_node->findChild(word[i]);
            if(tmp_node==nullptr){
                return false;
            }
            p_current_node = tmp_node;
        }
        if (p_current_node->isTerminal()){
                return true;
        }
        return false;
    }
    return false;
}
  

void Trie::deleteVect(Node* ptr_node, std::vector<Node*> &vect){
    if(vect.back() == ptr_node){
        vect.pop_back();
    }  
}


void Trie::renumbering(){
    Node* p_current_node;
    std::queue<Node*> queue;
    queue.push(head); 
    head->setColor(1);
    int num = 0;
    head->setColor(num);
    while(!queue.empty()){
        p_current_node = queue.front();
        queue.pop();
        for(auto& edge : p_current_node->getEdges()){   
            if(edge.second->getColor()==0){
                num++;
                edge.second->setNum(num);
                edge.second->setColor(1);
                queue.push(edge.second);                
            }  
        }         
   }
    number_of_nodes = num;
}


std::string Trie::storeDawg(){
    Node* p_current_node;
    std::queue<Node*> queue;
    queue.push(head); 
    head->setColor(0);
    std::string color = "";
    std::string result = "";
    std::string num = "";
    result=std::to_string(number_of_nodes+1)+"\n";
    while(!queue.empty()){
        p_current_node = queue.front();
        queue.pop();
        
        for(auto& edge : p_current_node->getEdges()){  
            num = std::to_string((edge.second)->getNum());
            
            result += num+edge.first;   
            if((edge.second)->isTerminal()){
               result+="#-";
            }
            else
                result+="-";
            if(edge.second->getColor()==1){
                edge.second->setColor(0);
                queue.push(edge.second);
            }  
            
        }
        result+="\n";
   }

    return result;
}


std::string Trie::toGraphvizFormat(){
    Node* p_current_node;
    std::queue<Node*> queue;
    queue.push(head); 
    head->setColor(1);
    std::string header = "digraph G {\n";
    std::string color = "";
    std::string body = "";
    std::string num = "";

    while(!queue.empty()){
        p_current_node = queue.front();
        queue.pop();
        
        for(auto& edge : p_current_node->getEdges()){  
            
            num = std::to_string((edge.second)->getNum());
            if((edge.second)->isTerminal()){
               color+=num+" [shape=doublecircle]\n";
            }
            body += std::to_string(p_current_node->getNum()) + "->" + num 
                    + " [label = "+edge.first+"];\n";  
            if(edge.second->getColor()==0){
                edge.second->setColor(1);
                queue.push(edge.second);
            }  
            
        }         
   }

    return header+color+body+"}";
}


void Trie::loadDawg(std::string path){       
    std::ifstream dawg(path.c_str(), std::ios::in);
    if(dawg){
        std::string line;
        std::string num_str="";
        Node* ptr_node;
        char letter;
        int num_current_node = 0;
        std::vector<Node*> nodes;
        //1ere ligne : nombre de noeuds
        getline(dawg, line);
        int i_max = std::stoi(line)+1;
        //creation de tous les noeuds avec leur num.
        nodes.push_back(head);
        for( int i = 1 ; i < i_max ; ++i ) {
            ptr_node = new Node(i);
            nodes.push_back(ptr_node);
        }
        //Creation des liens entre les noeuds
        while(getline(dawg, line)){
            ptr_node = nodes[num_current_node];
            for(int i = 0; i < line.length() ; ++i){
                if(line[i]>='0' && line[i]<='9'){
                    num_str+=line[i];
                }
                else{
                    //il y a deja eu un numero
                    if(num_str.length()>0){
                        if('a'<=line[i] && line[i]<='z'){
                            letter = line[i];
                        }
                        else {
                            if(line[i]=='-'){
                                nodes[num_current_node]->appendEdge(letter, nodes[std::stoi(num_str)]);
                                if(line[i-1]=='#'){
                                    nodes[std::stoi(num_str)]->setTerminal();
                                }
                                num_str = "";
                            }
                        }
                    }
                }
            }
            num_str="";                              
            num_current_node++;
        }
        number_of_nodes = num_current_node;
        dawg.close();
        std::cout<<"Dictionnaire chargé"<<std::endl;
    }
    else std::cout<<"Erreur d'ouverture du dictionnaire"<<std::endl;
}
    
    
void Trie::buildDawgAndStore(std::string pathDicoText, std::string pathResult){
    std::ifstream dicoText(pathDicoText.c_str(), std::ios::in);
    std::ofstream result(pathResult.c_str(), std::ios::out | std::ios::trunc);
    if(dicoText){
        std::string word;        
        std::cout<<"Dictionnaire ouvert"<<std::endl;
        while(getline(dicoText, word)){
            insertWord(word);
        }
        dicoText.close();
        std::cout<<"Dictionnaire fermé"<<std::endl;
        std::cout<<"Compression."<<std::endl;
        minimize();
        std::cout<<"Renumérotation."<<std::endl;
        renumbering();
        std::cout<<"Enregistrement du Dawg."<<std::endl;
        if(result){
            result<<storeDawg();
            result.close();
        }    
    }
    else {
        std::cerr<<"Erreur ouverture fichier";
    }
}
  

void Trie::findWords(std::string chevalet){
    int joker1_pos, joker2_pos;
    joker1_pos = chevalet.find('8', 0);
    if(joker1_pos != std::string::npos){
        joker2_pos = chevalet.find('8' , joker1_pos+1);
        if(joker2_pos != std::string::npos){
            for(char c1 = 'a' ; c1 <= 'z' ; ++c1){
                chevalet[joker1_pos] = c1;
                for(char c2 = c1 ; c2 <= 'z' ; ++c2){
                    chevalet[joker2_pos] = c2;
                    findWords(chevalet);
                }
            }
        }
        else {
            for(char c = 'a' ; c <= 'z' ; ++c){
                chevalet[joker1_pos]=c;
                findWords(chevalet);      
            }
        }
    }
    else findWords(head, chevalet, "");
}
 
/*
 * N'imp !!!!!!!!!!!!!!
 * a revoir cet algo de crotte
 */
void Trie::findWords(Node* p_node, std::string available_letters, std::string prefix){
    //std::cout<<"#"<<available_letters<<std::endl;
    Node* p_new_node;
    std::string new_letters;
    std::string word;
    char letter;
    for ( int i = 0 ; i < available_letters.length() ; ++i){
        new_letters="";
        letter = available_letters[i];
        p_new_node = p_node->findChild(letter);
        if(p_new_node!=nullptr){
            word=prefix+letter;
            for(int j = 0 ; j<available_letters.length() ; ++j){
                if(j<i)
                    new_letters+=available_letters[j];
                else
                    if(j>i)
                        new_letters+=available_letters[j];
            }
            if(p_new_node->isTerminal())
                //ajouter a l ensemble de mots
                std::cout<<word<<" trouvé dans le dictionnaire"<<std::endl;
            findWords(p_new_node, new_letters, word);
        }
    }
}