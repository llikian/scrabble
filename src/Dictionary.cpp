/***************************************************************************************************
 * @file  Dictionary.cpp
 * @brief Implementation of the Dictionary class
 **************************************************************************************************/

#include "Dictionary.hpp"

#include <algorithm>
#include <fstream>
#include "Board.hpp"

Node::Node(const char value, const bool isTerminal) : value(value), isTerminal(isTerminal) {
    for(Node*& child : children) {
        child = nullptr;
    }
}

Node*& Node::operator[](char letter) {
    if(letter >= 'A' && letter <= 'Z') { return children[letter - 'A']; }
    if(letter == '+') { return children[ALPHABET_SIZE]; }

    throw std::runtime_error("NOPE x(");
}

Node*& Node::getChild(char letter) {
    if(letter >= 'A' && letter <= 'Z') { return children[letter - 'A']; }
    if(letter == '+') { return children[ALPHABET_SIZE]; }

    throw std::runtime_error("NOPE x(");
}

Node::~Node() {
    for(const Node* child : children) {
        delete child;
    }
}

Dictionary::Dictionary() : root(new Node('\0', false)) { }

Dictionary::Dictionary(const std::string& loadPath) : root(new Node('\0', false)) {
    std::ifstream file(loadPath);
    if(!file.is_open()) {
        throw std::runtime_error("Couldn't open file \"" + loadPath + "\".");
    }

    std::string word;
    while(file >> word) {
        if(!word.empty() && word.size() <= BOARD_SIZE) {
            insertGADDAGWord(word);
        }
    }
}

Dictionary::~Dictionary() {
    delete root;
}

void Dictionary::insertWord(const std::string& word) {
    Node* current = root;

    for(char l : word) {
        if(l >= 'a' && l <= 'z') {
            l += 'A' - 'a';
        }

        Node*& child = current->getChild(l);
        if(child == nullptr) {
            child = new Node(l, false);
        }

        current = child;
    }

    current->isTerminal = true;
}

void Dictionary::insertGADDAGWord(const std::string& word) {
    std::string gaddagWord = '+' + word;

    // For each letter in the word, create a word by mirroring it around the '+'
    for(unsigned int i = 1 ; i < gaddagWord.length() ; i++) {
        std::rotate(gaddagWord.begin(), gaddagWord.begin() + i, gaddagWord.begin() + i + 1);

        insertWord(gaddagWord);
    }
}

bool Dictionary::containWord(const std::string& word) const {
    Node* current = root;

    for(char l : word) {
        Node* child = current->getChild(l);

        if(child == nullptr) {
            return false;
        }

        current = child;
    }

    return current->isTerminal;
}
