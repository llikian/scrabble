/***************************************************************************************************
 * @file  Player.cpp
 * @brief Implementation of the Player struct
 **************************************************************************************************/

#include "Player.hpp"

Player::Player(Bag& bag) : bag(bag), capacity(HAND_SIZE) {
    for(char letter : hand) {
        letter = bag.drawLetter();
    }
}
