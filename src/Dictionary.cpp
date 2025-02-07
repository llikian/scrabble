/***************************************************************************************************
 * @file  Dictionary.cpp
 * @brief Implementation of the Dictionary class
 **************************************************************************************************/

#include "Dictionary.hpp"

#include <algorithm>
#include <iostream>
#include <fstream>

Node::Node(const char value, const bool isTerminal) : value(value), isTerminal(isTerminal), children{} {

}

Dictionary::Dictionary() {
    root = new Node('\0', false);
}

Dictionary::Dictionary(const std::string& loadPath) {
    root = new Node('\0', false);

    std::ifstream file(loadPath);
    std::string str;

    while (std::getline(file, str)) {
        insertWord(str);
    }
}

Dictionary::Dictionary(const std::string& loadPath, const bool isGADAG) {
    root = new Node('\0', false);

    std::ifstream file(loadPath);
    std::string str;

    if (isGADAG) {
        while (std::getline(file, str)) {
            insertGADAGWord(str);
        }
    }
    else {
        while (std::getline(file, str)) {
            insertWord(str);
        }
    }
}

void Dictionary::insertWord(const std::string& word) {
    Node* current = root;

    for(char l: word) {
        if (l >= 'A' && l <= 'Z') {
            // Convert uppercase to lowercase by adding 32
            l += 32;
        }

        //if char is '+', put at the end, else put at alphabet position
        const int pos = l=='+' ? ALPHABET_SIZE : l - 'a';

        if(current->children[pos] == nullptr) {
            current->children[pos] = new Node(l, false);
        }
        current = current->children[pos];
    }
    current->isTerminal = true;
}

void Dictionary::insertGADAGWord(const std::string& word) {
    std::string gaddagWord = word;
    gaddagWord.insert(0, "+");

    //for each letter in the word, create a word by mirroring it around the '+'
    for(int i=0; i<static_cast<int>(gaddagWord.length()); i++) {
        std::rotate(gaddagWord.begin(), gaddagWord.begin() + i, gaddagWord.begin() + i+1);

        insertWord(gaddagWord);
    }

}


bool Dictionary::containWord(const std::string& word) {
    const Node* current = root;

    for(const char l: word) {
        //if char is '+', check at the end, else check at alphabet position
        const int pos = l=='+' ? ALPHABET_SIZE : l - 'a';

        if(current->children[pos] == nullptr) {
            return false;
        }
        current = current->children[pos];
    }
    return current->isTerminal;
}

