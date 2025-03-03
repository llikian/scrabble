/***************************************************************************************************
 * @file  Bag.cpp
 * @brief Implementation of the Bag struct
 **************************************************************************************************/

#include "Bag.hpp"

#include <iostream>
#include <random>

Bag::Bag() : letters(nullptr), size(0) {
    unsigned int totalLetters = 0;
    for(unsigned int letterCount : letterCounts) {
        totalLetters += letterCount;
    }

    letters = new char[totalLetters];
    for(int i = 0 ; i < ALPHABET_SIZE ; ++i) {
        for(unsigned int j = 0 ; j < letterCounts[i] ; ++j) {
            letters[size] = 'A' + i;
            ++size;
        }
    }

    if(size != totalLetters) {
        throw std::runtime_error("The bag was not filled.");
    }

    /* Shuffle using the Fisher-Yates method:
     * https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle#The_modern_algorithm
    */
    std::random_device device;
    std::default_random_engine rng(device());
    for(int i = size - 1 ; i > 0 ; --i) {
        std::swap(letters[i], letters[std::uniform_int_distribution<int>(0, i)(rng)]);
    }
}

Bag::~Bag() {
    delete[] letters;
}

char Bag::drawLetter() {
    if(size == 0) {
        return '\0';
    }

    return letters[--size];
}

unsigned int Bag::getPoints(char letter) {
    if(letter >= 'A' && letter <= 'Z') { return points[letter - 'A']; }
    if(letter >= 'a' && letter <= 'b') { return points[letter - 'a']; }
    return 0;
}

unsigned int Bag::getWordPoints(const std::string& word) {
    unsigned int points = 0;

    for(const char letter : word) {
        points += getPoints(letter);
    }

    return points;
}
