/***************************************************************************************************
 * @file  Dictionary.hpp
 * @brief Declaration of the Dictionary class
 **************************************************************************************************/

#pragma once

#include <string>
#include "Bag.hpp"

struct Node {
    char value;
    bool isTerminal;

    Node(char value, bool isTerminal);

    Node(const Node&) = delete;
    void operator=(const Node&) = delete;

    ~Node();

    Node*& child(char letter);

private:
    Node* children[ALPHABET_SIZE + 1]; // +1 for '+' character
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
    bool containWord(const std::string& word) const;

    static std::string getWordFromGaddagWord(const std::string& gaddagWord);

    static void unitTests();

private:
    void insertWord(const std::string& word);
};
