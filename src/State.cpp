/***************************************************************************************************
 * @file  State.cpp
 * @brief Implementation of the State struct
 **************************************************************************************************/

#include "State.hpp"

State::State(const Position& position, Node* node, const std::string& word, const Hand& hand, bool foundPlus)
    : position(position), node(node), word(word), hand(hand), foundPlus(foundPlus) { }
