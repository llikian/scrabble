/***************************************************************************************************
 * @file  Player.cpp
 * @brief Implementation of the Player struct
 **************************************************************************************************/

#include "Player.hpp"

#include <iostream>

Player::Player(Bag& bag)
    : bag(bag), capacity(HAND_SIZE), points(0) {
    init();
}

void Player::init() {
    capacity = HAND_SIZE;
    points = 0;

    for(char& letter : hand) {
        letter = bag.drawLetter();
    }
}

void Player::refreshHand(const std::string& usedLetters) { // TODO Very sus
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

void Player::setHand(char hand[7], unsigned int capacity) {
    this->capacity = capacity;
    for(unsigned int i = 0 ; i < capacity ; ++i) { this->hand[i] = hand[i]; }
}

Prediction MonteCarloPlayer::evaluateBoardRec(const Board& board, int maxMoveCheck, int maxForwardMoves) {
    std::vector<Move> moves = board.getAllMoves(Hand(*this));

    // Stop recursion if there is no move or maxForward move is reached
    if(maxForwardMoves <= 0 || moves.empty()) {
        return{Move(), points};
    }

    // Save player and bag state
    Bag bagSave;
    bagSave.copy(bag);
    char tmpHand[HAND_SIZE];
    int tmpCapacity = capacity;
    std::copy(std::begin(hand), std::end(hand), std::begin(tmpHand));
    int tmpPoints = points;

    Prediction bestMove(moves[0]);

    // For each possible move in the limit of moxMoveCheck
    for (int i = 0; i < std::min(maxMoveCheck,static_cast<int>(moves.size())); ++i) {

        // Copying the board and playing the move on it
        Board simBoard(board);
        playMove(simBoard, moves[i], false);

        // Recursion on the new board
        Prediction pred = evaluateBoardRec(simBoard, maxMoveCheck, maxForwardMoves - 1);

        // If the recursion give mor points, keep this move
        if(pred.possiblePoints > bestMove.possiblePoints) {
            bestMove.move = moves[i];
            bestMove.possiblePoints = pred.possiblePoints;
        }

        // Set player back to initial state
        bag.copy(bagSave);
        points = tmpPoints;
        std::copy(std::begin(tmpHand), std::end(tmpHand), std::begin(hand));
        capacity = tmpCapacity;
    }

    // Return the best potential move with its potential points
    return bestMove;
}

Move MonteCarloPlayer::getBestEvaluatedMove(const Board& board, int maxMoveCheck, int maxForwardMove, int iterations) {
    Move bestMove;
    bestMove.points = 0;

    // Make multiple iterations to smooth the variance
    for (int i = 0; i < iterations; ++i)
    {
        Move move = evaluateBoardRec(board, maxMoveCheck, maxForwardMove).move;
        if (move.points > bestMove.points)
            bestMove = move;
    }
    return bestMove;
}

bool MonteCarloPlayer::playBestMove(Board& board, bool verbose) {
    Move bestMove = getBestEvaluatedMove(board,3 ,3, 1);

    // No moves to play
    if (bestMove.points <= 0) return false;

    if(verbose) {
        std::cout << "Playing Montecarlo move : " << std::endl;
        std::cout << (bestMove.direction ? "[V] " : "[H] ");
        std::cout << '(' << bestMove.start.x << ", " << bestMove.start.y << ") ";
        std::cout << bestMove.word << " : " << bestMove.points << " points" << '\n';
    }

    playMove(board, bestMove, verbose);

    return true;
}
