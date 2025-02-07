/***************************************************************************************************
 * @file  Dictionary.cpp
 * @brief Implementation of the Dictionary class
 **************************************************************************************************/

#include "Dictionary.hpp"

#include <algorithm>
#include <iostream>
#include <fstream>
#include "Board.hpp"

Node::Node(const char value, const bool isTerminal) : value(value), isTerminal(isTerminal), children{} { }

Dictionary::Dictionary() : root(new Node('\0', false)) { }

Dictionary::Dictionary(const std::string& loadPath, bool isGADDAG) : root(new Node('\0', false)) {
    std::ifstream file(loadPath);
    std::string word;

    if(isGADDAG) {
        while(file >> word) {
            insertGADDAGWord(word);
        }
    } else {
        while(file >> word) {
            insertWord(word);
        }
    }
}

void Dictionary::insertWord(const std::string& word) {
    Node* current = root;

    for(char l: word) {
        if(l >= 'A' && l <= 'Z') {
            // Convert uppercase to lowercase by adding 32
            l += 32;
        }

        //if char is '+', put at the end, else put at alphabet position
        const int pos = l == '+' ? ALPHABET_SIZE : l - 'a';

        if(current->children[pos] == nullptr) {
            current->children[pos] = new Node(l, false);
        }

        current = current->children[pos];
    }

    current->isTerminal = true;
}

void Dictionary::insertGADDAGWord(const std::string& word) {
    std::string gaddagWord = word;
    gaddagWord.insert(0, "+");

    //for each letter in the word, create a word by mirroring it around the '+'
    for(int i = 0 ; i < static_cast<int>(gaddagWord.length()) ; i++) {
        std::rotate(gaddagWord.begin(), gaddagWord.begin() + i, gaddagWord.begin() + i + 1);

        insertWord(gaddagWord);
    }
}


bool Dictionary::containWord(const std::string& word) {
    const Node* current = root;

    for(const char l: word) {
        //if char is '+', check at the end, else check at alphabet position
        const int pos = l == '+' ? ALPHABET_SIZE : l - 'a';

        if(current->children[pos] == nullptr) {
            return false;
        }

        current = current->children[pos];
    }

    return current->isTerminal;
}

