/***************************************************************************************************
 * @file  Board.hpp
 * @brief Declaration of the Board struct
 **************************************************************************************************/

#pragma once

#include <stack>
#include <string>
#include <vector>
#include "Bag.hpp"
#include "Dictionary.hpp"
#include "Player.hpp"
#include "Spot.hpp"

#define BOARD_SIZE 15

enum Direction : bool {
    VERTICAL,
    HORIZONTAL
};

struct State {
    Position position;
    Node* node;
    std::vector<char> letters;
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
    BonusType getBonusType(int row, int column);

    void findBestMove(Player& player);
private:
    Spot board[BOARD_SIZE][BOARD_SIZE];
    const Bag& bag;
    const Dictionary& dictionay;

    Move* handleStackState(std::stack<State>& stack, const Spot* spot, const State& state, Direction direction);
};