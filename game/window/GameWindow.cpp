#include "GameWindow.h"
#include <iostream>

GameWindow::GameWindow() : window(nullptr), renderer(nullptr) {}

GameWindow::~GameWindow() {
    close();
}

bool GameWindow::init(bool fullscreen) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (fullscreen) {
        // Get current display mode for the primary display
        SDL_DisplayMode current;
        if (SDL_GetDesktopDisplayMode(0, &current) != 0) {
            std::cerr << "Could not get desktop display mode: " << SDL_GetError() << std::endl;
            return false;
        }
        window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  current.w, current.h, SDL_WINDOW_FULLSCREEN);
    } else {
        window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  800, 600, SDL_WINDOW_SHOWN);
    }

    if (!window) {
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        return false;
    }

    return true;
}

void GameWindow::close() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

SDL_Renderer* GameWindow::getRenderer() const {
    return renderer;
}

int GameWindow::getWidth() const {
    int width;
    if (window) {
        SDL_GetWindowSize(window, &width, nullptr);
        return width;
    }
    return 0;
}

int GameWindow::getHeight() const {
    int height;
    if (window) {
        SDL_GetWindowSize(window, nullptr, &height);
        return height;
    }
    return 0;
}
