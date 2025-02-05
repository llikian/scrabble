/***************************************************************************************************
 * @file  Bag.hpp
 * @brief Declaration of the Bag struct
 **************************************************************************************************/

#pragma once

#define ALPHABET_SIZE 26

/**
 * @struct Bag
 * @brief
 */
struct Bag {
public:
    Bag();
    ~Bag();

    char drawLetter();

    unsigned int getPoints(char letter) const;

private:
    char* letters;
    unsigned int size;
    unsigned int capacity;

    const constexpr static unsigned int letterCounts[ALPHABET_SIZE]{9, 2, 2, 3, 15, 2, 2, 2, 8, 1, 1, 5, 3,
                                                                    6, 6, 2, 1, 6, 6, 6, 6, 2, 1, 1, 1, 1};
    const constexpr static unsigned int points[ALPHABET_SIZE]{1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 10, 1, 2,
                                                              1, 1, 3, 8, 1, 1, 1, 1, 4, 10, 10, 10, 10};
};