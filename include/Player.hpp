/***************************************************************************************************
 * @file  Player.hpp
 * @brief Declaration of the Player struct
 **************************************************************************************************/

#pragma once

#include "Board.hpp"
#include "Bag.hpp"

/**
 * @struct Player
 * @brief
 */
struct Player {
    Player(Bag& bag);
    virtual ~Player() = default;

    Bag& bag;
    char hand[HAND_SIZE];
    unsigned int capacity;
    unsigned int points;

    void refreshHand(const std::string& usedLetters);

    void playMove(Board& board, const Move& move);
    virtual void playBestMove(Board& board);
};

struct Prediction {
    Move* move;
    int possiblePoints;

    Prediction(Move* move): move(move), possiblePoints(0) {}
};

struct MonteCarloPlayer : Player {

    Prediction evaluateMove(const Move& move, int maxForwardMoves);
    Move evaluateAllMoves(const std::vector<Move>& moves, int maxWordCheck, int maxForwardMoves);

    void playBestMove(Board& board) override;
};
