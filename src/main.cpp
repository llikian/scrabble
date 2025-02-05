/***************************************************************************************************
 * @file  main.cpp
 * @brief Contains the main program of the engine
 **************************************************************************************************/

#include <iostream>
#include <stdexcept>

#include "Application.hpp"

int SDL_main(int, char**) {
    try {
        Application().run();
    } catch(const std::exception& exception) {
        std::cerr << "ERROR : " << exception.what() << '\n';
        return -1;
    }

    return 0;
}