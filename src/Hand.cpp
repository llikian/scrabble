/***************************************************************************************************
 * @file  Hand.cpp
 * @brief Implementation of the Hand struct
 **************************************************************************************************/

#include "Hand.hpp"

Hand::Hand(const Player& player) : capacity(player.capacity) {
    for(unsigned int i = 0 ; i < capacity ; ++i) {
        letters[i] = player.hand[i];
    }
}

Hand::Hand(const Hand& hand) : capacity(hand.capacity) {
    for(unsigned int i = 0 ; i < capacity ; ++i) {
        letters[i] = hand.letters[i];
    }
}

Hand::Hand(const Hand& hand, unsigned int removedLetterIndex) : capacity(0) {
    for(unsigned int i = 0 ; i < hand.capacity ; ++i) {
        if(i != removedLetterIndex) {
            letters[capacity] = hand.letters[i];
            capacity++;
        }
    }
}

void Hand::operator=(const Hand& hand) {
    capacity = hand.capacity;

    for(unsigned int i = 0 ; i < capacity ; ++i) {
        letters[i] = hand.letters[i];
    }
}
