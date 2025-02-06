/***************************************************************************************************
 * @file  Dictionary.cpp
 * @brief Implementation of the Dictionary class
 **************************************************************************************************/

#include "Dictionary.hpp"

Node::Node(const char value, const bool isTerminal) : value(value), isTerminal(isTerminal), children{} {

}

Dictionary::Dictionary() {
    root = new Node('\0', false);
}

Dictionary::Dictionary(const std::string& loadPath) {
    root = new Node('\0', false);

    std::ifstream file(loadPath);
    std::string str;
    while (std::getline(file, str))
    {
        insertWord(str);
    }
}

void Dictionary::insertWord(const std::string& word) {
    Node* current = root;

    for(const char l: word) {
        if(current->children[l - 'a'] == nullptr) {
            current->children[l - 'a'] = new Node(l, false);
        }
        current = current->children[l - 'a'];
    }
    current->isTerminal = true;
}


bool Dictionary::containWord(const std::string& word) {
    const Node* current = root;

    for(const char i: word) {
        if(current->children[i - 'a'] == nullptr) {
            return false;
        }
        current = current->children[i - 'a'];
    }
    return current->isTerminal;
}

