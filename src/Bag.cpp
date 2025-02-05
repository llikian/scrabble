/***************************************************************************************************
 * @file  Bag.cpp
 * @brief Implementation of the Bag struct
 **************************************************************************************************/

#include "Bag.hpp"

#include <iostream>

Bag::Bag() : letters(nullptr), size(0), capacity(0) {
    srand(time(nullptr));

    for(unsigned int letterCount: letterCounts) {
        capacity += letterCount;
    }

    letters = new char[capacity];
    for(int i = 0 ; i < ALPHABET_SIZE ; ++i) {
        for(unsigned int j = 0 ; j < letterCounts[i] ; ++j) {
            letters[size] = 'a' + i;
            ++size;
        }
    }

    if(size != capacity) {
        throw std::runtime_error("The bag was not filled.");
    }

    /* Shuffle using the Fisher-Yates method:
     * https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle#The_modern_algorithm
     */
    int j;
    char tmp;
    for(int i = size - 1 ; i >= 1 ; --i) {
        j = rand() % (i + 1);

        tmp = letters[i];
        letters[i] = letters[j];
        letters[j] = tmp;
    }

    for(int i = 0 ; i < size ; ++i) {
        std::cout << letters[i] << ' ';
    }
}

Bag::~Bag() {
    delete[] letters;
}

char Bag::drawLetter() {
    if(size == 0) {
        return '\0';
    }

    char letter = letters[size];
    --size;

    return letter;
}

unsigned int Bag::getPoints(char letter) const {
    if(letter >= 'A' && letter <= 'Z') {
        return points[letter - 'A'];
    } else if(letter >= 'a' && letter <= 'b') {
        return points[letter - 'a'];
    } else {
        return 0;
    }
}
