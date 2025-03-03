/***************************************************************************************************
 * @file  State.hpp
 * @brief Declaration of the State struct
 **************************************************************************************************/

#pragma once

#include "Dictionary.hpp"
#include "Hand.hpp"
#include "Position.hpp"

/**
 * @struct State
 * @brief
 */
struct State {
    State(const Position& position, Node* node, const std::string& word, const Hand& hand);

    State(const Position& position, Node* node, const std::string& word, const Hand& hand, bool foundPlus);

    Position position;
    Node* node;
    std::string word; // Word as it is in the gaddag
    Hand hand;
    bool foundPlus;
};
