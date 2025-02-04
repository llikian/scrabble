/***************************************************************************************************
 * @file  Application.hpp
 * @brief Declaration of the Application class
 **************************************************************************************************/

#pragma once

#include <SDL2/SDL.h>
#include <unordered_map>

#include "Spot.hpp"

#define BOARD_SIZE 15

/**
 * @class Application
 * @brief
 */
class Application {
public:
    Application();
    ~Application();

    void run();

private:
    void handleEvents();
    void handleInputs(SDL_Scancode scancode);

    SDL_Window* window;
    SDL_Renderer* renderer;

    int width, height;

    Spot board[BOARD_SIZE][BOARD_SIZE];

    bool stop;
    std::unordered_map<SDL_Scancode, bool> keysFlags;
};