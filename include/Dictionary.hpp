/***************************************************************************************************
 * @file  Dictionary.hpp
 * @brief Declaration of the Dictionary class
 **************************************************************************************************/

#pragma once

#include <string>
#include "Bag.hpp"

#define LOWERCASE_TO_UPPERCASE(l) l -= 32

struct Node {
    char value;
    bool isTerminal;
    Node* children[ALPHABET_SIZE + 1]; // +1 for '+' character

    Node(char value, bool isTerminal);
};

//Trie structure
class Dictionary {
public:
    Node* root;

    Dictionary();
    Dictionary(const std::string& loadPath);
    ~Dictionary();

    Dictionary(const Dictionary&) = delete;
    void operator=(const Dictionary&) = delete;

    void insertGADDAGWord(const std::string& word);
    bool containWord(const std::string& word);

    static void unitTests();
private:
    void insertWord(const std::string& word);
};
