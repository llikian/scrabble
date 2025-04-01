/***************************************************************************************************
 * @file  Player.cpp
 * @brief Implementation of the Player struct
 **************************************************************************************************/

#include "Player.hpp"

#include <iostream>

Player::Player(Bag& bag)
    : bag(bag), capacity(HAND_SIZE), points(0) {
    for(char& letter : hand) {
        letter = bag.drawLetter();
    }
}

void Player::refreshHand(const std::string& usedLetters) {
    for(char used_letter : usedLetters) {
        for(char& c : hand) {
            if(c == used_letter) {
                c = bag.drawLetter();
                if(c == '\0') { --capacity; }
                break;
            }
        }
    }

    // Make sure the letters are continuous and at the beginning of the array
    if(capacity < HAND_SIZE) {
        int pos = 0;

        for(int i = 0 ; i < HAND_SIZE ; ++i) {
            if(hand[i] != '\0') {
                hand[pos++] = hand[i];
            }
        }

        while(pos < HAND_SIZE) { hand[pos++] = '\0'; }
    }
}

void Player::playMove(Board& board, const Move& move, bool verbose) {
    std::string usedLetters;

    bool backward = true;
    Position spotPos(move.start.x, move.start.y);

    // Place move word on board
    for(int i = 0 ; i < static_cast<int>(move.word.length()) ; ++i) {
        if(move.word[i] == '+') { // End of backward path
            spotPos.x = move.start.x + move.direction;
            spotPos.y = move.start.y + !move.direction;
            backward = false;
            continue;
        }

        if(spotPos.x >= BOARD_SIZE || spotPos.y >= BOARD_SIZE) continue;

        Spot* currentSpot = &board.board[spotPos.x][spotPos.y];
        if(currentSpot->isEmpty()) {
            currentSpot->character = move.word[i];

            usedLetters += move.word[i];
            if(verbose) {
                std::cout << "Placed letter " << board.board[spotPos.x][spotPos.y].character <<
                    " at " << currentSpot->position.x << ", " << currentSpot->position.y << '\n';
            }
        } else if(currentSpot->character != move.word[i]) { // Placing another letter on taken spot
            throw std::runtime_error("Placing invalid letter " + move.word[i]);
        }

        // Move on board in wanted direction
        if(backward) {
            spotPos.x -= move.direction;
            spotPos.y -= !move.direction;
        } else {
            spotPos.x += move.direction;
            spotPos.y += !move.direction;
        }
    }

    // Add move points to player
    points += move.points;

    // Remove used letters from player hand
    refreshHand(usedLetters);
}

bool Player::playBestMove(Board& board, bool verbose) {
    std::vector<Move> moves = board.getAllMoves(Hand(*this));
    if(moves.empty()) { return false; }

    Move bestMove = moves[0];

    if(verbose) {
        std::cout << "Playing most points move : " << std::endl;
        std::cout << (bestMove.direction ? "[V] " : "[H] ");
        std::cout << '(' << bestMove.start.x << ", " << bestMove.start.y << ") ";
        std::cout << bestMove.word << " : " << bestMove.points << " points" << '\n';
    }

    playMove(board, bestMove, verbose);

    return true;
}

Prediction MonteCarloPlayer::evaluateMove(const Move& move, int iterations, int maxForwardMoves, float maxPonderTime) {
    int points = 0;

    for(int i = 0 ; i < iterations ; ++i) {
        // Add to points the points gained by (until end of game/maxForwardMoves) moves
    }

    return { move, points / iterations };
}

Move MonteCarloPlayer::getBestEvaluatedMove(const std::vector<Move>& moves,
                                            int iterations,
                                            int maxForwardMoves,
                                            int maxMoveCheck,
                                            float maxPonderTime) {
    if(moves.empty()) {
        throw std::runtime_error(std::string("MonteCarlo Player : No moves to play"));
    }

    if(maxMoveCheck <= 0) maxMoveCheck = moves.size();

    Prediction bestMove(moves[0]);

    for(int i = 0 ; i < maxMoveCheck ; ++i) {
        Prediction pred = evaluateMove(moves[i], iterations, maxForwardMoves, maxPonderTime);
        if(pred.possiblePoints > bestMove.possiblePoints) bestMove = pred;
    }

    return bestMove.move;
}

bool MonteCarloPlayer::playBestMove(Board& board, bool verbose) {
    Move bestMove = getBestEvaluatedMove(board.getAllMoves(Hand(*this)), 10);

    if(verbose) {
        std::cout << "Playing Big Brain move : " << std::endl;
        std::cout << (bestMove.direction ? "[V] " : "[H] ");
        std::cout << '(' << bestMove.start.x << ", " << bestMove.start.y << ") ";
        std::cout << bestMove.word << " : " << bestMove.points << " points" << '\n';
    }

    playMove(board, bestMove, verbose);

    return true;
}
