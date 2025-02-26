/***************************************************************************************************
 * @file  Board.hpp
 * @brief Declaration of the Board struct
 **************************************************************************************************/

#pragma once

#include <string>
#include "Bag.hpp"
#include "Dictionary.hpp"
#include "Player.hpp"
#include "Spot.hpp"

#define BOARD_SIZE 15

enum Direction : bool {
    VERTICAL,
    HORIZONTAL
};

struct Hand {
    Hand(const Player& player);
    Hand(const Hand& hand);
    Hand(const Hand& hand, int removedLetterIndex);
    void operator=(const Hand& hand);

    char letters[7];
    int capacity;
};

struct State {
    State(const Position& position, Node* node, const std::string& word, const Hand& hand);

    State(const Position& position, Node* node, const std::string& word, const Hand& hand, bool foundPlus);

    Position position;
    Node* node;
    std::string word; // Word as it is in the gaddag
    Hand hand;
    bool foundPlus;
};

struct Move {
    Position start; // Position where the search started
    Direction direction;
    std::string word; // Word as it is in the gaddag
};

/**
 * @struct Board
 * @brief
 */
struct Board {
public:
    Board(const Bag& bag, const Dictionary& dictionary);

    void loadFromFile(const std::string& path);
    void saveToFile(const std::string& path) const;

    char& operator ()(int row, int column);
    BonusType getBonusType(int row, int column) const;

    void findBestMove(Player& player);

private:
    Spot board[BOARD_SIZE][BOARD_SIZE];
    const Bag& bag;
    const Dictionary& dictionay;
};
