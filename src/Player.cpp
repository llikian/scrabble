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

void Player::drawHand()
{
    for (char & c : hand) {
        if(c == '\0') {
            c = bag.drawLetter();
            break;
        }
    }
}