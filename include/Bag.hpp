/***************************************************************************************************
 * @file  Bag.hpp
 * @brief Declaration of the Bag struct
 **************************************************************************************************/

#pragma once

#define ALPHABET_SIZE 26
#include <string>

/**
 * @struct Bag
 * @brief
 */
struct Bag {
public:
    Bag();
    ~Bag();

    void init();
    void copy(const Bag& bag);
    char drawLetter();

    static unsigned int getPoints(char letter);
    static unsigned int getWordPoints(const std::string& word);

private:
    char* letters;
    unsigned int size;

    constexpr static unsigned char letterCounts[ALPHABET_SIZE]{
        9, 2, 2, 3, 15, 2, 2, 2, 8, 1, 1, 5, 3,
        6, 6, 2, 1, 6, 6, 6, 6, 2, 1, 1, 1, 1
    };
    constexpr static unsigned char points[ALPHABET_SIZE]{
        1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 10, 1, 2,
        1, 1, 3, 8, 1, 1, 1, 1, 4, 10, 10, 10, 10
    };
};
