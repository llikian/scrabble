/***************************************************************************************************
 * @file  Application.hpp
 * @brief Declaration of the Application class
 **************************************************************************************************/

#pragma once

extern "C" {
#include <SDL2/SDL.h>
}

#include <unordered_map>

#define BOARD_SIZE 15

enum class Cell {
    None,
    LetterX2,
    LetterX3,
    WordX2,
    WordX3
};

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

    Cell board[BOARD_SIZE][BOARD_SIZE];

    bool stop;
    std::unordered_map<SDL_Scancode, bool> keysFlags;
};