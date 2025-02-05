/***************************************************************************************************
 * @file  Player.cpp
 * @brief Implementation of the Player struct
 **************************************************************************************************/

#include "Player.hpp"

Player::Player(Bag& bag) : bag(bag), capacity(HAND_SIZE), points(0) {
    for(char letter : hand) {
        letter = bag.drawLetter();
    }
}
