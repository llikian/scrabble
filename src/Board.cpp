/***************************************************************************************************
 * @file  Board.cpp
 * @brief Implementation of the Board struct
 **************************************************************************************************/

#include "Board.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <unordered_set>
#include "State.hpp"

Board::Board(const Bag& bag, const Dictionary& dictionary)
    : bag(bag), dictionary(dictionary) {
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

bool Board::isPositionValid(const Position& position) const {
    return position.x < BOARD_SIZE && position.y < BOARD_SIZE;
}

bool Board::isCoordinateValid(unsigned int coord) const {
    return coord < BOARD_SIZE;
}

char& Board::operator ()(int row, int column) {
    return board[row][column].character;
}

BonusType Board::getBonusType(int row, int column) const {
    return board[row][column].type;
}

int Board::getWordPoints(const Spot& startSpot, char startLetter, const Direction& direction) const {
    std::string word{ startLetter };
    Position spotPos(startSpot.position.x - direction, startSpot.position.y - !direction);

    while(isPositionValid(spotPos) && !board[spotPos.x][spotPos.y].isEmpty()) {
        word += board[spotPos.x][spotPos.y].character;
        spotPos.x -= direction;
        spotPos.y -= !direction;
    }

    word += '+';
    spotPos.x = startSpot.position.x + direction;
    spotPos.y = startSpot.position.y + !direction;

    while(isPositionValid(spotPos) && !board[spotPos.x][spotPos.y].isEmpty()) {
        word += board[spotPos.x][spotPos.y].character;
        spotPos.x += direction;
        spotPos.y += !direction;
    }

    // The letter doesn't create new words
    if(word.length() <= 2) { return 0; }

    if(dictionary.containWord(word)) { return Bag::getWordPoints(word); }

    // The letter creates invalid words
    return -1;
}

void Board::applyBonusPoints(Move& move) const {
    int letterUsed = 0;
    int wordMultiplier = 1;
    Position spotPos(move.start.x, move.start.y);
    bool backward = true;

    for(int i = 0 ; i < static_cast<int>(move.word.length()) ; ++i) {
        if(move.word[i] == '+') { // End of backward path
            spotPos.x = move.start.x + move.direction;
            spotPos.y = move.start.y + !move.direction;
            backward = false;
            continue;
        }

        if(spotPos.x >= BOARD_SIZE || spotPos.y >= BOARD_SIZE) { continue; }

        Spot currentSpot = board[spotPos.x][spotPos.y];

        // Check for crossing words
        int adjacentWordPoints = getWordPoints(currentSpot, move.word[i], static_cast<Direction>(!move.direction));
        // Perpendicular direction
        if(adjacentWordPoints == -1) { // Crossing invalid words, move is invalid
            // std::cout<<"Filtered move " << move.word << " by crossing invalid words" << std::endl;
            move.points = 0;
            return;
        }

        if(currentSpot.isEmpty()) {
            // Apply bonus of the spot
            switch(currentSpot.type) {
                case BonusType::None:
                    move.points += Bag::getPoints(move.word[i]);
                    break;
                case BonusType::LetterX2:
                    move.points += Bag::getPoints(move.word[i]) * 2;
                    break;
                case BonusType::LetterX3:
                    move.points += Bag::getPoints(move.word[i]) * 3;
                    break;
                case BonusType::WordX2:
                    move.points += Bag::getPoints(move.word[i]);
                    wordMultiplier *= 2;
                    break;
                case BonusType::WordX3:
                    move.points += Bag::getPoints(move.word[i]);
                    wordMultiplier *= 3;
                    break;
            }

            letterUsed++;
            move.points += adjacentWordPoints; // Only take crossing word point if it is created with a new letter
        } else {
            //If it's not a new character from this move, don't apply bonus
            move.points += Bag::getPoints(move.word[i]);
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
    move.points *= wordMultiplier;

    // Scrabble !
    if(letterUsed == HAND_SIZE) move.points += 50;
}

void Board::sortMoveByPoints(std::vector<Move>& moves) const {
    std::sort(moves.begin(), moves.end(), operator>);
}

void Board::checkForWords(const Hand& hand,
                          const Spot* startSpot,
                          std::vector<Move>& moves,
                          const Direction& direction) const {
    std::queue<State> queue;

    State init(startSpot->position, dictionary.root, "", hand, false);
    queue.push(init);
    while(!queue.empty()) {
        const State& state = queue.front();

        const Spot& spot = board[state.position.x][state.position.y];
        const unsigned int shift = state.foundPlus ? 1 : -1;

        if(spot.isEmpty()) {
            // We found a correct word
            if(state.node->isTerminal) {
                Position nextPos = direction
                                       ? Position(state.position.x + 1, state.position.y)
                                       : Position(state.position.x, state.position.y + 1);

                if(!isPositionValid(nextPos) || board[nextPos.x][nextPos.y].isEmpty()) {
                    Move move(startSpot->position, direction, state.word, 0);
                    applyBonusPoints(move);

                    if(move.points > 0) { // If the move is valid
                        // std::cout<<"Added move " << move.word << " for " << move.points << " points" << std::endl;
                        moves.emplace_back(move);
                    }
                }
            }

            // There is a path labeled with a '+' in the GADDAG
            if(Node* node = state.node->child('+') ; node != nullptr) {
                Position position = direction
                                        ? Position(startSpot->position.x + 1, startSpot->position.y)
                                        : Position(startSpot->position.x, startSpot->position.y + 1);

                if(isPositionValid(position)) {
                    queue.emplace(position, node, state.word + '+', state.hand, true);
                }
            }

            // Create a new state on the stack for each letter from the hand that could be placed
            for(unsigned int i = 0 ; i < state.hand.capacity ; ++i) {
                const char& letter = state.hand.letters[i];
                if(Node* node = state.node->child(letter) ; node != nullptr) {
                    Position position = direction
                                            ? Position(state.position.x + shift, state.position.y)
                                            : Position(state.position.x, state.position.y + shift);

                    if(isPositionValid(position)) {
                        queue.emplace(position, node, state.word + letter, Hand(state.hand, i), state.foundPlus);
                    }
                }
            }
        } else if(Node* node = state.node->child(spot.character) ; node != nullptr) {
            // There is a path labeled with the letter on the spot in the GADDAG
            Position position = direction
                                    ? Position(state.position.x + shift, state.position.y)
                                    : Position(state.position.x, state.position.y + shift);

            if(isPositionValid(position)) {
                queue.emplace(position, node, state.word + spot.character, state.hand, state.foundPlus);
            }
        }

        queue.pop();
    }
}

std::vector<Move> Board::getAllMoves(const Hand& hand, const bool print) const {
    /* ---- Find possible start positions ---- */
    std::unordered_set<const Spot*> startPositions;
    std::vector<Move> moves;

    for(int i = 0 ; i < BOARD_SIZE ; ++i) {
        for(int j = 0 ; j < BOARD_SIZE ; ++j) {
            if(board[i][j].character != '\0') { // The spot has a letter on it
                if(i + 1 < BOARD_SIZE && board[i + 1][j].isEmpty()) { startPositions.emplace(&board[i + 1][j]); }
                if(j + 1 < BOARD_SIZE && board[i][j + 1].isEmpty()) { startPositions.emplace(&board[i][j + 1]); }
                if(i > 0 && board[i - 1][j].isEmpty()) { startPositions.emplace(&board[i - 1][j]); }
                if(j > 0 && board[i][j - 1].isEmpty()) { startPositions.emplace(&board[i][j - 1]); }
            }
        }
    }

    // No starting positions were found
    if(startPositions.empty()) {
        if(board[7][7].isEmpty()) { // This is the first move
            startPositions.emplace(&board[7][7]);
        } else { // The board is somehow full
            std::cout << "No starting positions were found.\n";
            return moves; // Empty vector
        }
    }

    for(const Spot* startSpot : startPositions) {
        checkForWords(hand, startSpot, moves, HORIZONTAL);
        checkForWords(hand, startSpot, moves, VERTICAL);
    }

    sortMoveByPoints(moves);

    if(print) {
        for(const auto& [start, direction, word, points] : moves) {
            std::cout << (direction ? "[V] " : "[H] ");
            std::cout << '(' << start.x << ", " << start.y << ") ";
            std::cout << word << " : " << points << " points" << '\n';
        }
    }

    return moves;
}

bool Board::testAllWordsOnBoard() const {
    constexpr static Direction directions[2]{ VERTICAL, HORIZONTAL };

    for(Direction direction : directions) {
        for(int i = BOARD_SIZE - 1 ; i >= 0 ; --i) {
            std::string word;

            for(int j = BOARD_SIZE - 1 ; j >= 0 ; --j) {
                if(direction ? board[i][j].isEmpty() : board[j][i].isEmpty()) {
                    word.clear();
                    continue;
                }

                Position nextPos = direction ? Position(i, j - 1) : Position(j - 1, i);
                word += direction ? board[i][j].character : board[j][i].character;

                if(word.size() > 1 && (!isPositionValid(nextPos) || board[nextPos.x][nextPos.y].isEmpty())) {
                    if(!dictionary.containWord(word + '+')) {
                        std::reverse(word.begin(), word.end());
                        std::cout << "Incorrect word \"" << word << "\" found.\n";
                        return false;
                    }

                    std::reverse(word.begin(), word.end());
                    std::cout << "Correct word \"" << word << "\" found.\n";
                    word.clear();
                }
            }
        }
    }

    return true;
}
