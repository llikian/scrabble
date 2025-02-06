//
// Created by Foyeur on 06/02/2025.
//

#include "Dictionary.hpp"

#include <algorithm>

Node::Node(const char value, const bool isTerminal) : value(value), isTerminal(isTerminal), children{}
{

}

Dictionary::Dictionary()
{
    root = new Node('\0', false);
}

void Dictionary::insertWord(const std::string& word)
{
    Node* current = root;

    for (int i = 0; i < word.size(); i++)
    {
        if (current->children[word[i] - 'a'] == nullptr)
            current->children[word[i] - 'a'] = new Node(word[i] - 'a', false);
        current = current->children[word[i] - 'a'];
    }
    current->isTerminal = true;
}


bool Dictionary::containWord(const std::string& word)
{
    return false;
}

