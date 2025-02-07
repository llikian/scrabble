/***************************************************************************************************
 * @file  Dictionary.hpp
 * @brief Declaration of the Dictionary class
 **************************************************************************************************/

#pragma once

#include <Bag.hpp>
#include <string>

struct Node {
    char value;
    bool isTerminal;
    Node* children[ALPHABET_SIZE + 1]; //+1 for '+' character

    Node(char value, bool isTerminal);
};

//Trie structure
class Dictionary {
private:
public:
    Node* root;

    Dictionary();
    Dictionary(const std::string& loadPath, bool isGADDAG = false);

    void insertWord(const std::string& word);
    void insertGADDAGWord(const std::string& word);
    bool containWord(const std::string& word);
};


