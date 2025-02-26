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

struct Hand {
    Hand(const Player& player)
        : capacity(player.capacity) {
        for(int i = 0 ; i < capacity ; ++i) {
            letters[i] = player.hand[i];
        }
    }

    Hand(const Hand& hand)
        : capacity(hand.capacity) {
        for(int i = 0 ; i < capacity ; ++i) {
            letters[i] = hand.letters[i];
        }
    }

    Hand(const Hand& hand, int removedLetterIndex)
        : capacity(0) {
        for(int i = 0 ; i < hand.capacity ; ++i) {
            if(i != removedLetterIndex) {
                letters[capacity] = hand.letters[i];
                capacity++;
            }
        }
    }

    void operator=(const Hand& hand) {
        capacity = hand.capacity;

        for(int i = 0 ; i < capacity ; ++i) {
            letters[i] = hand.letters[i];
        }
    }

    char letters[7];
    int capacity;
};

struct State {
    State(const Position& position, Node* node, const Hand& hand) : position(position), node(node), hand(hand) { }

    Position position;
    Node* node;
    std::string word; // Word as it is in the gaddag
    Hand hand;
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
