/***************************************************************************************************
 * @file  Application.cpp
 * @brief Implementation of the Application class
 **************************************************************************************************/

#include "Application.hpp"

#include <iostream>
#include <stdexcept>

Application::Application()
    : window(nullptr), renderer(nullptr), font(nullptr),
      width(1200), height(800),
      stop(false),
      player(bag),
      squareLength(0) {

    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(std::string("SDL_Init failed: ").append(SDL_GetError()));
    }

    if(TTF_Init() != 0) {
        throw std::runtime_error(std::string("TTF_Init failed: ") + SDL_GetError());
    }

    Uint32 windowFlags = (SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    window = SDL_CreateWindow("Scrabble", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, windowFlags);
    if(window == nullptr) {
        throw std::runtime_error(std::string("Couldn't create window: ") + SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(renderer == nullptr) {
        throw std::runtime_error(std::string("Couldn't create renderer: ") + SDL_GetError());
    }

    font = TTF_OpenFont("data/fonts/courbd.ttf", 20);
    if(font == nullptr) {
        throw std::runtime_error(std::string("Couldn't open font: ") + SDL_GetError());
    }

    handleResize();

    /* ---- Initialize Board ---- */
    static const char rawBoard[BOARD_SIZE][BOARD_SIZE + 1]{
        "3..d...3...d..3",
        ".2...t...t...2.",
        "..2...d.d...2..",
        "d..2...d...2..d",
        "....2.....2....",
        ".t...t...t...t.",
        "..d...d.d...d..",
        "3..d...2...d..3",
        "..d...d.d...d..",
        ".t...t...t...t.",
        "....2.....2....",
        "d..2...d...2..d",
        "..2...d.d...2..",
        ".2...t...t...2.",
        "3..d...3...d..3"
    };

    for(int i = 0 ; i < BOARD_SIZE ; ++i) {
        for(int j = 0 ; j < BOARD_SIZE ; ++j) {
            board[i][j].character = '\0';

            switch(rawBoard[i][j]) {
                case '.':
                    board[i][j].type = BonusType::None;
                    break;
                case 'd':
                    board[i][j].type = BonusType::LetterX2;
                    break;
                case 't':
                    board[i][j].type = BonusType::LetterX3;
                    break;
                case '2':
                    board[i][j].type = BonusType::WordX2;
                    break;
                case '3':
                    board[i][j].type = BonusType::WordX3;
                    break;
                default:
                    throw std::runtime_error("Invalid character in board creation.");
            }
        }
    }
}

Application::~Application() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Application::run() {
    while(!stop) {
        handleEvents();

        setColor(62, 53, 48);
        SDL_RenderClear(renderer);

        drawBoard();

        SDL_RenderPresent(renderer);
    }
}

void Application::setColor(Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
}

void Application::drawSquare(int x, int y, int length) {
    SDL_Rect square(x, y, length, length);
    SDL_RenderFillRect(renderer, &square);
}

void Application::drawHorizontalLine(int x, int y, int length) {
    SDL_RenderDrawLine(renderer, x, y, x + length, y);
}

void Application::drawVerticalLine(int x, int y, int length) {
    SDL_RenderDrawLine(renderer, x, y, x, y + length);
}

void Application::drawText(int x, int y, const std::string& text, Uint8 r, Uint8 g, Uint8 b) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), SDL_Color(r, g, b, 255));
    if(surface == nullptr) {
        throw std::runtime_error(std::string("TTF_RenderText_Solid failed: ") + SDL_GetError());
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(texture == nullptr) {
        SDL_FreeSurface(surface);
        throw std::runtime_error(std::string("SDL_CreateTextureFromSurface failed: ") + SDL_GetError());
    }

    SDL_Rect rect(x, y, surface->w, surface->h);
    SDL_RenderCopy(renderer, texture, nullptr, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Application::drawCenteredText(const SDL_Rect& reference, const std::string& text, Uint8 r, Uint8 g, Uint8 b) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), SDL_Color(r, g, b, 255));
    if(surface == nullptr) {
        throw std::runtime_error(std::string("TTF_RenderText_Solid failed: ") + SDL_GetError());
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(texture == nullptr) {
        SDL_FreeSurface(surface);
        throw std::runtime_error(std::string("SDL_CreateTextureFromSurface failed: ") + SDL_GetError());
    }

    SDL_Rect rect(reference.x + (reference.w - surface->w) / 2, reference.y + (reference.h - surface->h) / 2,
                  surface->w, surface->h);
    SDL_RenderCopy(renderer, texture, nullptr, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Application::handleEvents() {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_KEYDOWN:
                handleInputs(event.key.keysym.scancode);

                break;
            case SDL_KEYUP:
                if(keysFlags.contains(event.key.keysym.scancode)) {
                    keysFlags[event.key.keysym.scancode] = false;
                }

                break;
            case SDL_QUIT:
                stop = true;

                break;
            case SDL_WINDOWEVENT:
                if(event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    handleResize();
                }

                break;
            default:
                break;
        }
    }
}

void Application::handleInputs(SDL_Scancode scancode) {
    switch(scancode) {
        case SDL_SCANCODE_ESCAPE:
            stop = true;
            break;
        default:
            break;
    }
}

void Application::handleResize() {
    SDL_GetWindowSize(window, &width, &height);
    TTF_SetFontSize(font, 0.8f * (std::min(width, height) - 20) / 15);

    if(width < height) {
        squareLength = (width - 20) / BOARD_SIZE;
        boardStart.x = 10;
        boardStart.y = (height - width) / 2;
    } else {
        squareLength = (height - 20) / BOARD_SIZE;
        boardStart.x = (width - height) / 2;
        boardStart.y = 10;
    }
}

void Application::drawBoard() {
    SDL_Rect rect;
    char text[1];

    board[7][7].character = 'A';
    board[8][7].character = 'V';
    board[9][7].character = 'I';
    board[10][7].character = 'O';
    board[11][7].character = 'N';
    board[12][7].character = 'S';

    /* ---- Draw Board ---- */
    rect.w = rect.h = squareLength;

    for(int i = 0 ; i < BOARD_SIZE ; ++i) {
        for(int j = 0 ; j < BOARD_SIZE ; ++j) {
            switch(board[i][j].type) {
                case BonusType::None:
                    text[0] = '\0';
                    setColor(103, 88, 78);
                    break;
                case BonusType::LetterX2:
                    text[0] = '2';
                    setColor(123, 182, 255);
                    break;
                case BonusType::LetterX3:
                    text[0] = '3';
                    setColor(76, 104, 255);
                    break;
                case BonusType::WordX2:
                    text[0] = '2';
                    setColor(255, 148, 202);
                    break;
                case BonusType::WordX3:
                    text[0] = '3';
                    setColor(255, 85, 85);
                    break;
            }

            rect.x = boardStart.x + squareLength * i;
            rect.y = boardStart.y + squareLength * j;

            drawSquare(rect.x, rect.y, squareLength);

            if(board[i][j].character != '\0') {
                setColor(238, 195, 166);
                drawSquare(rect.x + 5, rect.y + 5, squareLength - 10);

                text[0] = board[i][j].character;
                drawCenteredText(rect, text, 103, 88, 78);
            } else if(text[0] != '\0') {
                drawCenteredText(rect, text, 255, 255, 255);
            }
        }
    }

    setColor(255, 255, 255);
    for(int i = 0 ; i <= BOARD_SIZE ; ++i) {
        drawVerticalLine(boardStart.x + squareLength * i, boardStart.y, squareLength * BOARD_SIZE);
        drawHorizontalLine(boardStart.x, boardStart.y + squareLength * i, squareLength * BOARD_SIZE);
    }
}
