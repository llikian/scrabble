//
// Created by Foyeur on 06/02/2025.
//

#include "Dictionary.hpp"

#include <algorithm>

Node::Node(const char value, const bool isTerminal) : value(value), isTerminal(isTerminal){ }

Dictionary::Dictionary()
{
    root = new Node('\0', false);
}

void Dictionary::insertWord(const std::string& word)
{

}


bool Dictionary::containWord(const std::string& word)
{
    return false;
}

