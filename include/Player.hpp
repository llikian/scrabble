/***************************************************************************************************
 * @file  Player.hpp
 * @brief Declaration of the Player struct
 **************************************************************************************************/

#pragma once

#include "Bag.hpp"
#include "Board.hpp"

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

    void playMove(Board& board, const Move& move, bool verbose);
    virtual bool playBestMove(Board& board, bool verbose = true);
};

struct Prediction {
    Move move;
    int possiblePoints;

    Prediction(const Move move): move(move), possiblePoints(0) {}
    Prediction(const Move move, int points): move(move), possiblePoints(points) {}
};

struct MonteCarloPlayer : Player {
    using Player::Player;

    Prediction evaluateMove(const Move& move, int iterations, int maxForwardMoves = 0, float maxPonderTime = 0);
    Move getBestEvaluatedMove(const std::vector<Move>& moves, int iterations, int maxForwardMoves = 0, int maxMoveCheck = 0, float maxPonderTime = 0);

    bool playBestMove(Board& board, bool verbose) override;
};
