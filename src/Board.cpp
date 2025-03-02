/***************************************************************************************************
 * @file  Board.cpp
 * @brief Implementation of the Board struct
 **************************************************************************************************/

#include "Board.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <unordered_set>

Hand::Hand(const Player& player)
    : capacity(player.capacity) {

    for(int i = 0 ; i < capacity ; ++i) {
        letters[i] = player.hand[i];
    }
}

Hand::Hand(const Hand& hand)
    : capacity(hand.capacity) {

    for(int i = 0 ; i < capacity ; ++i) {
        letters[i] = hand.letters[i];
    }
}

Hand::Hand(const Hand& hand, int removedLetterIndex)
    : capacity(0) {

    for(int i = 0 ; i < hand.capacity ; ++i) {
        if(i != removedLetterIndex) {
            letters[capacity] = hand.letters[i];
            capacity++;
        }
    }
}

void Hand::operator=(const Hand& hand) {
    capacity = hand.capacity;

    for(int i = 0 ; i < capacity ; ++i) {
        letters[i] = hand.letters[i];
    }
}

State::State(const Position& position, Node* node, const std::string& word, const Hand& hand)
    : position(position), node(node), word(word), hand(hand), foundPlus(false) { }

State::State(const Position& position, Node* node, const std::string& word, const Hand& hand, bool foundPlus)
    : position(position), node(node), word(word), hand(hand), foundPlus(foundPlus) { }

bool Move::compareByPoints(const Move& m1, const Move& m2)
{
    return m1.points > m2.points;
}

Board::Board(const Bag& bag, const Dictionary& dictionary)
    : bag(bag), dictionay(dictionary) {

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

int Board::getWordPoints(const Spot& startSpot, const Direction& direction) const
{
    std::string word;
    Position spotPos(startSpot.position.x, startSpot.position.y);

    while (spotPos.x < BOARD_SIZE && spotPos.y < BOARD_SIZE && board[spotPos.x][spotPos.y].character != '\0')
    {
        word += board[spotPos.x][spotPos.y].character;
        spotPos.x -= direction;
        spotPos.y -= !direction;
    }

    word += '+';
    spotPos.x = startSpot.position.x + direction;
    spotPos.y = startSpot.position.y + !direction;

    while (spotPos.x < BOARD_SIZE && spotPos.y < BOARD_SIZE && board[spotPos.x][spotPos.y].character != '\0')
    {
        word += board[spotPos.x][spotPos.y].character;
        spotPos.x += direction;
        spotPos.y += !direction;
    }

    // The letter don't create new words
    if (word.length() <= 1)
        return 0;

    if (dictionay.containWord(word))
        return Bag::getWordPoints(word);

    // The letter create invalid words
    return -1;
}

void Board::applyBonusPoints(Move& move) const
{
    int letterUsed = 0;
    int wordMultiplier = 1;
    Position spotPos(move.start.x, move.start.y);
    bool backward = true;

    for (int i = 0; i < static_cast<int>(move.word.length()); ++i)
    {
        if (move.word[i] == '+') // End of backward path
        {
            spotPos.x = move.start.x  + move.direction;
            spotPos.y = move.start.y  + !move.direction;
            backward = false;
            continue;
        }
        if(spotPos.x >= BOARD_SIZE || spotPos.y >= BOARD_SIZE)
            continue;

        Spot currentSpot = board[spotPos.x][spotPos.y];

        // Check for crossing words
        int adjacentWordPoints = getWordPoints(currentSpot, static_cast<Direction>(!move.direction)); // Perpendicular direction
        if (adjacentWordPoints == -1) { //Crossing invalid words, move is invalid
            move.points = 0;
            return;
        }

        if (currentSpot.character != '\0')
        {
            //If it's not a new character from this move, don't apply bonus
            move.points += Bag::getPoints(move.word[i]);
        }
        else
        {
            // Apply bonus of the spot
            switch (currentSpot.type)
            {
            case BonusType::None:
                move.points += Bag::getPoints(move.word[i]);
                break;
            case BonusType::LetterX2:
                move.points += (Bag::getPoints(move.word[i]) * 2);
                break;
            case BonusType::LetterX3:
                move.points += (Bag::getPoints(move.word[i]) * 3);
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
        }

        // Move on board in wanted direction
        if (backward) {
            spotPos.x -= move.direction;
            spotPos.y -= !move.direction;
        }
        else {
            spotPos.x += move.direction;
            spotPos.y += !move.direction;
        }
    }
    move.points *= wordMultiplier;

    // Scrabble !
    if (letterUsed >= 7)
        move.points += 50;
}

void Board::sortMoveByPoints(std::vector<Move>& moves) const
{
    std::sort(moves.begin(), moves.end(), Move::compareByPoints);
}

void Board::checkForWords(Player& player, const Spot* startSpot, std::vector<Move>& moves, const Direction& direction) const
{
    std::stack<State> stack;

    State init(startSpot->position, dictionay.root, "", Hand(player));
    stack.push(init);
    while(!stack.empty()) {
        const State top = stack.top();
        stack.pop();

        const Spot& spot = board[top.position.x][top.position.y];

        if(spot.character == '\0') { // Spot is empty
            // We found a correct word
            if(top.node->isTerminal) {
                Move move(startSpot->position, direction, top.word, 0);
                applyBonusPoints(move);

                if (move.points > 0) // If the move is valid
                    moves.emplace_back(move);
            }

            // There is a path labeled with a '+' in the GADDAG
            if(Node* node = top.node->getChild('+') ; node != nullptr) {
                // Add 1 to current direction
                Position pos(startSpot->position.x + direction, startSpot->position.y + !direction);
                stack.emplace(pos, node, top.word + '+', top.hand, true);
            }

            // Create a new state on the stack for each letter from the hand that could be placed
            for(int i = 0 ; i < top.hand.capacity ; ++i) {
                if(Node* node = top.node->getChild(top.hand.letters[i]) ; node != nullptr) {
                    Position position = direction
                        ? Position(top.position.x + (top.foundPlus ? 1 : -1), top.position.y)
                        : Position(top.position.x, top.position.y + top.foundPlus ? 1 : -1);

                    if(direction ? top.position.x : top.position.y < BOARD_SIZE) {
                        stack.emplace(position, node, top.word + top.hand.letters[i], Hand(top.hand, i));
                    }
                }
            }
        } else if(Node* node = top.node->getChild(spot.character) ; node != nullptr) {
            // There is a path labeled with the letter on the spot in the GADDAG
            Position position = direction
                ? Position(top.position.x + (top.foundPlus ? 1 : -1), top.position.y)
                : Position(top.position.x, top.position.y + (top.foundPlus ? 1 : -1));


            if(direction ? top.position.x : top.position.y < BOARD_SIZE) {
                stack.emplace(position, node, top.word + spot.character, top.hand);
            }
        }
    }
}

std::vector<Move> Board::getAllMoves(Player& player, const bool print) const {
    /* ---- Find possible start positions ---- */
    std::unordered_set<const Spot*> startPositions;
    std::vector<Move> moves;

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

    // No starting positions were found
    if(startPositions.empty()) {
        if(board[8][8].character == '\0') { // This is the first move
            startPositions.emplace(&board[8][8]);
        } else { // The game is over
            std::cout << "No starting positions were found.\n";
            return moves; //Empty vector
        }
    }

    for(const Spot* startSpot : startPositions) {
        checkForWords(player, startSpot, moves, HORIZONTAL);
        checkForWords(player, startSpot, moves, VERTICAL);
    }

    sortMoveByPoints(moves);

    if (print) {
        for(const auto& [start, direction, word, points] : moves) {
            std::cout << (direction ? "[V] " : "[H] ");
            std::cout << '(' << start.x << ", " << start.y << ") ";
            std::cout << word << " : " << points << " points" << '\n';
        }
    }

    return moves;
}

Move Board::getMostPointsMove(Player& player) const
{
    return getAllMoves(player)[0];
}

void Board::playMove(Player& player, const Move& move)
{
    std::string usedLetters;

    bool backward = true;
    Position spotPos(move.start.x, move.start.y);

    //Place move word on board
    for (int i = 0; i < static_cast<int>(move.word.length()); ++i)
    {
        if (move.word[i] == '+') // End of backward path
        {
            spotPos.x = move.start.x  + move.direction;
            spotPos.y = move.start.y  + !move.direction;
            backward = false;
            continue;
        }
        if(spotPos.x >= BOARD_SIZE || spotPos.y >= BOARD_SIZE)
            continue;

        Spot* currentSpot = &board[spotPos.x][spotPos.y];
        if (currentSpot->character == '\0') {
            currentSpot->character = move.word[i];

            usedLetters += move.word[i];
            std::cout<<"Placed letter "<< board[spotPos.x][spotPos.y].character <<
                " at " << currentSpot->position.x <<"," << currentSpot->position.y << std::endl;
        }
        else if (currentSpot->character != move.word[i]) //Placing another letter on taken spot
        {
            throw std::runtime_error("Placing invalid letter " + move.word[i]);
        }

        // Move on board in wanted direction
        if (backward) {
            spotPos.x -= move.direction;
            spotPos.y -= !move.direction;
        }
        else {
            spotPos.x += move.direction;
            spotPos.y += !move.direction;
        }
    }

    //Add move points to player
    player.points += move.points;

    //Remove used letters from player hand
    for (auto used_letter : usedLetters) {
        for (char & c : player.hand) {
            if(c == used_letter) {
                c = '\0';
                break;
            }
        }
    }
    player.drawHand();
}

void Board::playMostPointsMove(Player& player)
{
    Move bestMove = getMostPointsMove(player);

    std::cout<<"Playing best move : "<<std::endl;
    std::cout << (bestMove.direction ? "[V] " : "[H] ");
    std::cout << '(' << bestMove.start.x << ", " << bestMove.start.y << ") ";
    std::cout << bestMove.word << " : " << bestMove.points << " points" << '\n';

    playMove(player, bestMove);
}
