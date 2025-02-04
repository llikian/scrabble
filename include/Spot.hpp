/***************************************************************************************************
 * @file  Spot.hpp
 * @brief Declaration of the Spot struct
 **************************************************************************************************/

#pragma once

#include "Bonus.hpp"

#include <iostream>

/* A spot on the board to place a letter */

struct Spot {
    //default initialization, no letter, no bonus
    Spot();

    //bonus spot initialization
    // * lf is the bonus letter factor
    // * wf is the bonus word factor
    Spot(unsigned char lf, unsigned char wf);

    //the letter placed on the spot, 0 if none
    char letter;

    //the bonus present on the spot
    Bonus bonus;
};

//display of the spot contents
std::ostream& operator <<(std::ostream& out, Spot s);
