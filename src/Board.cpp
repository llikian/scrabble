/***************************************************************************************************
 * @file  Board.cpp
 * @brief Implementation of the Board struct
 **************************************************************************************************/

#include "Board.hpp"

#include <fstream>
#include <stdexcept>
#include <iostream>
#include <unordered_set>

Board::Board(const Bag& bag, const Dictionary& dictionary) : bag(bag), dictionay(dictionary) {
    static constexpr char rawBoard[BOARD_SIZE][BOARD_SIZE + 1]{
        "3..d...3...d..3",
        ".2...t...t...2.",
        "..2...d.d...2..",
        "d..2...d...2..d",
        "....2.....2....",
        ".t...t...t...t.",
        "..d...d.d...d..",
        "3..d...2...d..3",
        "..d...d.d...d..",
        ".t...t...t...t.",
        "....2.....2....",
        "d..2...d...2..d",
        "..2...d.d...2..",
        ".2...t...t...2.",
        "3..d...3...d..3"
    };

    for(int i = 0 ; i < BOARD_SIZE ; ++i) {
        for(int j = 0 ; j < BOARD_SIZE ; ++j) {
            board[i][j].character = '\0';
            board[i][j].position.x = i;
            board[i][j].position.y = j;

            switch(rawBoard[i][j]) {
                case '.':
                    board[i][j].type = BonusType::None;
                    break;
                case 'd':
                    board[i][j].type = BonusType::LetterX2;
                    break;
                case 't':
                    board[i][j].type = BonusType::LetterX3;
                    break;
                case '2':
                    board[i][j].type = BonusType::WordX2;
                    break;
                case '3':
                    board[i][j].type = BonusType::WordX3;
                    break;
                default:
                    throw std::runtime_error("Invalid character in board creation.");
            }
        }
    }
}

void Board::loadFromFile(const std::string& path) {
    std::ifstream file(path);
    if(!file.is_open()) {
        throw std::runtime_error("Could not open file \"" + path + "\".");
    }

    char letter;

    for(int i = 0 ; i < BOARD_SIZE ; ++i) {
        for(int j = 0 ; j < BOARD_SIZE ; ++j) {
            file >> letter;

            if(letter >= 'A' && letter <= 'Z') {
                board[i][j].character = letter;
            } else {
                board[i][j].character = '\0';
            }
        }
    }
}

void Board::saveToFile(const std::string& path) const {
    std::ofstream file(path);
    if(!file.is_open()) {
        throw std::runtime_error("Could not create or open file \"" + path + "\".");
    }

    for(int i = 0 ; i < BOARD_SIZE ; ++i) {
        for(int j = 0 ; j < BOARD_SIZE ; ++j) {
            const char& letter = board[i][j].character;

            if(letter >= 'A' && letter <= 'Z') {
                file << letter;
            } else {
                file << '.';
            }
        }

        file << '\n';
    }
}

char& Board::operator ()(int row, int column) {
    return board[row][column].character;
}

BonusType Board::getBonusType(int row, int column) const {
    return board[row][column].type;
}

void Board::findBestMove(Player& player) {
    /* ---- Find possible start positions ---- */
    std::unordered_set<Spot*> startPositions;

    for(int i = 0 ; i < BOARD_SIZE ; ++i) {
        for(int j = 0 ; j < BOARD_SIZE ; ++j) {
            if(board[i][j].character != '\0') { // The spot has a letter on it
                if(board[i + 1][j].character == '\0') { startPositions.emplace(&board[i + 1][j]); }
                if(board[i][j + 1].character == '\0') { startPositions.emplace(&board[i][j + 1]); }
                if(board[i - 1][j].character == '\0') { startPositions.emplace(&board[i - 1][j]); }
                if(board[i][j - 1].character == '\0') { startPositions.emplace(&board[i][j - 1]); }
            }
        }
    }

    if(startPositions.empty()) { // No starting positions were found
        if(board[8][8].character == '\0') { // This is the first move
            startPositions.emplace(&board[8][8]);
        } else { // The game is over
            std::cout << "No starting positions were found.\n";
        }
    }

    /* ---- Find all possible words ---- */
    std::stack<State> stack;
    std::vector<Move> moves; // Defined on the heap so need deleting

    for(const Spot* spot: startPositions) {
        // Add initial state to stack
        State init(spot->position, dictionay.root, Hand(player));

        // Check for words horizontally
        stack.push(init);
        while(!stack.empty()) {
            State top = stack.top();
            stack.pop();

        }

        // Check for words vertically
        stack.push(init);
        while(!stack.empty()) {
            State top = stack.top();
            stack.pop();


        }
    }
}
