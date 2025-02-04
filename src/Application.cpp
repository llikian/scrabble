/***************************************************************************************************
 * @file  Application.cpp
 * @brief Implementation of the Application class
 **************************************************************************************************/

#include "Application.hpp"

#include <stdexcept>

Application::Application()
    : window(nullptr), renderer(nullptr),
      width(1280), height(780),
      stop(false) {

    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(std::string("SDL_Init failed : ").append(SDL_GetError()));
    }

    Uint32 windowFlags = (SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    window = SDL_CreateWindow("Scrabble", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, windowFlags);
    if(window == nullptr) {
        throw std::runtime_error(std::string("Window was not created : ").append(SDL_GetError()));
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(renderer == nullptr) {
        throw std::runtime_error(std::string("Renderer was not created : ").append(SDL_GetError()));
    }

    /* ---- Initialize Board ---- */
    static const char rawBoard[BOARD_SIZE][BOARD_SIZE + 1] {
        "3--d---3---d--3",
        "-2---t---t---2-",
        "--2---d-d---2--",
        "d--t---d---t--d",
        "----2-----2----",
        "-t---t---t---t-",
        "--d---d-d---d--",
        "3--d---2---d--3",
        "--d---d-d---d--",
        "-t---t---t---t-",
        "----2-----2----",
        "d--t---d---t--d",
        "--2---d-d---2--",
        "-2---t---t---2-",
        "3--d---3---d--3"
    };

    for(int i = 0 ; i < BOARD_SIZE ; ++i) {
        for(int j = 0 ; j < BOARD_SIZE ; ++j) {
            switch(rawBoard[i][j]) {
                case '-':
                    board[i][j] = Cell::None;
                    break;
                case 'd':
                    board[i][j] = Cell::LetterX2;
                    break;
                case 't':
                    board[i][j] = Cell::LetterX3;
                    break;
                case '2':
                    board[i][j] = Cell::WordX2;
                    break;
                case '3':
                    board[i][j] = Cell::WordX3;
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
    SDL_Rect rect;

    while(!stop) {
        handleEvents();

        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        rect.x = 0;
        rect.y = 0;
        rect.w = 50;
        rect.h = 50;
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
    }
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
                    SDL_GetWindowSize(window, &width, &height);
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
//        case SDL_SCANCODE_F11:
//            if(!keysFlags[scancode]) {
//                SDL_SetWindowFullscreen(window, fullscreen ? 0 : SDL_WINDOW_FULLSCREEN);
//                fullscreen = !fullscreen;
//                keysFlags[SDL_SCANCODE_F11] = true;
//            }
//
//            break;
        default:
            break;
    }
}
