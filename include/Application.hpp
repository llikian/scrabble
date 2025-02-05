/***************************************************************************************************
 * @file  Application.hpp
 * @brief Declaration of the Application class
 **************************************************************************************************/

#pragma once

#include <SDL.h>
#include "SDL_ttf.h"
#include <string>
#include <unordered_map>

#include "Bag.hpp"
#include "Player.hpp"
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

    void setColor(Uint8 r, Uint8 g, Uint8 b);

    void drawSquare(int x, int y, int length);
    void drawHorizontalLine(int x, int y, int length);
    void drawVerticalLine(int x, int y, int length);

    void drawText(int x, int y, const std::string& text, Uint8 r, Uint8 g, Uint8 b);
    void drawCenteredText(const SDL_Rect& reference, const std::string& text, Uint8 r, Uint8 g, Uint8 b);

private:
    void handleEvents();
    void handleInputs(SDL_Scancode scancode);
    void handleResize();

    void drawBoard();

    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;

    int width, height;

    bool stop;
    std::unordered_map<SDL_Scancode, bool> keysFlags;

    Spot board[BOARD_SIZE][BOARD_SIZE];
    Bag bag;
    Player player;

    SDL_Point boardStart;
    int squareLength;
};