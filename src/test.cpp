/***************************************************************************************************
 * @file  test.cpp
 * @brief Contains the unit tests for the project
 **************************************************************************************************/

#include <iostream>

#include "Dictionary.hpp"
#include "Hand.hpp"

int main() {
    Dictionary::unitTests();
    Hand::unitTests();

    return 0;
}
