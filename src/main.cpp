/***************************************************************************************************
 * @file  main.cpp
 * @brief Contains the main program of the engine
 **************************************************************************************************/

#include <iostream>
#include <stdexcept>

#include "Application.hpp"
#include "Test.hpp"

int main(int, char**) {
    //testAll();

    try {
        Application().run();
    } catch(const std::exception& exception) {
        std::cerr << "ERROR : " << exception.what() << '\n';
        return -1;
    }

    return 0;
}