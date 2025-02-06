/***************************************************************************************************
 * @file  Dictionary.cpp
 * @brief Implementation of the Dictionary class
 **************************************************************************************************/

#include "Dictionary.hpp"

#include <algorithm>

Node::Node(const char value, const bool isTerminal) : value(value), isTerminal(isTerminal), children{} {

}

Dictionary::Dictionary() {
    root = new Node('\0', false);
}

void Dictionary::insertWord(const std::string& word) {
    Node* current = root;

    for(const char i: word) {
        if(current->children[i - 'a'] == nullptr) {
            current->children[i - 'a'] = new Node(i - 'a', false);
        }
        current = current->children[i - 'a'];
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

