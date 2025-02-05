/***************************************************************************************************
 * @file  Bag.cpp
 * @brief Implementation of the Bag struct
 **************************************************************************************************/

#include "Bag.hpp"

Bag::Bag() {
    for(int i = 0 ; i < ALPHABET_SIZE ; ++i) {
        for(unsigned int j = 0 ; j < totalLetters[i] ; ++j) {
            letters.push_back('a' + i);
        }
    }

    std::shuffle(letters.begin(), letters.end(), std::default_random_engine(time(nullptr)));
}

char Bag::drawLetter() {
    if(letters.empty()) {
        return '\0';
    }

    char letter = letters.back();
    letters.pop_back();

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
