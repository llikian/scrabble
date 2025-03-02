/***************************************************************************************************
 * @file  Player.cpp
 * @brief Implementation of the Player struct
 **************************************************************************************************/

#include "Player.hpp"

Player::Player(Bag& bag)
    : bag(bag), capacity(HAND_SIZE), points(0) {

    for(char& letter : hand) {
        letter = bag.drawLetter();
    }
}

void Player::refreshHand(const std::string& usedLetters)
{
    for (char used_letter : usedLetters) {
        for (char & c : hand) {
            if(c == used_letter) {
                c = bag.drawLetter();
                if(c == 0) {
                    --capacity;
                }
                break;
            }
        }
    }
}