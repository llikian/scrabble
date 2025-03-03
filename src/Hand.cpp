/***************************************************************************************************
 * @file  Hand.cpp
 * @brief Implementation of the Hand struct
 **************************************************************************************************/

#include "Hand.hpp"

#include <cassert>
#include <iostream>

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

void Hand::unitTests() {
    std::cout << "Hand Unit Tests:\n";

    /* Player Constructor Test */ {
        Bag bag;
        Player player(bag);
        Hand hand(player);

        assert(hand.capacity == player.capacity);
        for(unsigned int i = 0 ; i < player.capacity ; ++i) {
            assert(hand.letters[i] == player.hand[i]);
        }

        std::cout << "  Player Constructor Test passed !\n";
    }

    /* Copy Constructor Test */ {
        Bag bag;
        Player player(bag);
        Hand hand(player);
        Hand copy(hand);

        assert(copy.capacity == hand.capacity);
        for(unsigned int i = 0 ; i < hand.capacity ; ++i) {
            assert(copy.letters[i] == hand.letters[i]);
        }

        std::cout << "  Copy Constructor Test passed !\n";
    }

    /* Remove Letter Copy Constructor Test */ {
        Bag bag;
        Player player(bag);
        Hand hand(player);

        for(unsigned int i = 0 ; i < hand.capacity ; ++i) {
            Hand copy(hand, i);

            assert(copy.capacity == hand.capacity - 1);

            for(int j = 0 ; j < i ; ++j) {
                assert(copy.letters[j] == hand.letters[j]);
            }

            for(int j = i ; j < hand.capacity - 1 ; ++j) {
                assert(copy.letters[j] == hand.letters[j + 1]);
            }
        }

        std::cout << "  Remove Letter Copy Constructor Test passed !\n";
    }

    /* Copy Operator Test */ {
        Bag bag;
        Player player(bag);
        Hand hand(player);
        Hand copy = hand;

        assert(copy.capacity == hand.capacity);
        for(unsigned int i = 0 ; i < hand.capacity ; ++i) {
            assert(copy.letters[i] == hand.letters[i]);
        }

        std::cout << "  Copy Operator Test passed !\n";
    }

    std::cout << "All Hand Unit Tests passed !\n\n";
}
