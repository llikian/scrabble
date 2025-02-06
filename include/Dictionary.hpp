/***************************************************************************************************
* @file  Dictionary.hpp
 * @brief Declaration of the dictionary class
 **************************************************************************************************/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <Bag.hpp>
#include <string>

struct Node
{
    char value;
    bool isTerminal;
    Node* children[ALPHABET_SIZE];

    Node(char value, bool isTerminal);
};

//Trie structure
class Dictionary {
private:
    Node* root;

public:
    Dictionary();

    void insertWord(const std::string& word);
    bool containWord(const std::string& word);
};



#endif //DICTIONARY_H
