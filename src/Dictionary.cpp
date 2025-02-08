/***************************************************************************************************
 * @file  Dictionary.cpp
 * @brief Implementation of the Dictionary class
 **************************************************************************************************/

#include "Dictionary.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include "Board.hpp"

Node::Node(const char value, const bool isTerminal) : value(value), isTerminal(isTerminal), children{} { }

Dictionary::Dictionary() : root(new Node('\0', false)) { }

Dictionary::Dictionary(const std::string& loadPath, bool isGADDAG) : root(new Node('\0', false)) {
    std::ifstream file(loadPath);
    if(!file.is_open()) {
        throw std::runtime_error("Couldn't open file \"" + loadPath +"\".");
    }

    std::string word;

    if(isGADDAG) {
        while(file >> word) {
            if(!word.empty() && word.size() <= BOARD_SIZE) {
                insertGADDAGWord(word);
            }
        }
    } else {
        while(file >> word) {
            if(!word.empty() && word.size() <= BOARD_SIZE) {
                insertWord(word);
            }
        }
    }
}

void Dictionary::insertWord(const std::string& word) {
    Node* current = root;

    for(char l: word) {
        if(l >= 'a' && l <= 'z') {
            LOWERCASE_TO_UPPERCASE(l);
        }

        // If char is '+', put at the end, else put at alphabet position
        const int pos = l == '+' ? ALPHABET_SIZE : l - 'A';

        if(current->children[pos] == nullptr) {
            current->children[pos] = new Node(l, false);
        }

        current = current->children[pos];
    }

    current->isTerminal = true;
}

void Dictionary::insertGADDAGWord(const std::string& word) {
    int len = word.length();

    std::string gaddagWord = word;
    gaddagWord.insert(0, "+");

    // For each letter in the word, create a word by mirroring it around the '+'
    for(int i = 1 ; i <= len ; i++) {
        std::rotate(gaddagWord.begin(), gaddagWord.begin() + i, gaddagWord.begin() + i + 1);

        insertWord(gaddagWord);
    }
}

bool Dictionary::containWord(const std::string& word) {
    const Node* current = root;

    for(const char l: word) {
        // If char is '+', check at the end, else check at alphabet position
        const int pos = l == '+' ? ALPHABET_SIZE : l - 'A';

        if(current->children[pos] == nullptr) {
            return false;
        }

        current = current->children[pos];
    }

    return current->isTerminal;
}