/***************************************************************************************************
 * @file  main.cpp
 * @brief Contains the main program of the engine
 **************************************************************************************************/

#include <iostream>
#include <stdexcept>
#include <vector>

#include "Application.hpp"

#define ALPHABET_SIZE 26
#define HAND_SIZE 7

struct Bag {
    Bag() {
        for(int i = 0 ; i < ALPHABET_SIZE ; ++i) {
            for(unsigned int j = 0 ; j < totalLetters[i] ; ++j) {
                bag.push_back('a' + i);
            }
        }

//        std::shuffle(bag.begin(), bag.end(), );
    }

    char getRandomLetter() {
        if(bag.empty()) {
            return '\0';
        }

        char letter = bag.back();
        bag.pop_back();

        return letter;
    }

    int getPoints(char letter) {
        return points[letter - 'a'];
    }

private:
    std::vector<char> bag;

    const constexpr static unsigned int totalLetters[ALPHABET_SIZE]{9, 2, 2, 3, 15, 2, 2, 2, 8, 1, 1, 5, 3,
                                                                          6, 6, 2, 1, 6, 6, 6, 6, 2, 1, 1, 1, 1};
    const constexpr static unsigned int points[ALPHABET_SIZE]{1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 10, 1, 2,
                                                              1, 1, 3, 8, 1, 1, 1, 1, 4, 10, 10, 10, 10};
};

struct Player {
    Player(Bag& bag) : bag(bag), capacity(HAND_SIZE) {
        for(char letter : hand) {
            letter = bag.getRandomLetter();
        }
    }

    Bag& bag;
    char hand[HAND_SIZE];
    unsigned int capacity;
};

int main() {
    try {
        Application().run();
    } catch(const std::exception& exception) {
        std::cerr << "ERROR : " << exception.what() << '\n';
        return -1;
    }

    return 0;
}