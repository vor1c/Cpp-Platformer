#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "GameWindow.h"
#include "Player.h"
#include "FPSCounter.h"

const std::string fontPath = "fonts/Rubik-Medium.ttf";
const int fontSize = 24;
const int SPEED = 200; // Pixels per second
const int FPS_CAP = 180;
const int SCREEN_TICK_PER_FRAME = 1000 / FPS_CAP;

int main(int argc, char *args[]) {
    std::cout << "Starting the game..." << std::endl;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          800, 600, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (!window) {
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    if (TTF_Init() == -1) {
        std::cerr << "TTF could not initialize! SDL Error: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    TTF_Font *font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Nach der Erstellung des Fensters
    int screenWidth, screenHeight;
    SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);

// Übergeben Sie diese Werte an die `Player`-Instanz
    Player player(100, 100, 50, 50, screenWidth, screenHeight);
    FPSCounter fpsCounter;

    SDL_Color textColor = {255, 255, 255, 255}; // White color for text
    SDL_Event e;
    bool quit = false;
    Uint32 lastTick = SDL_GetTicks(), currentTick;
    Uint32 frameStart, frameTime;

    while (!quit) {
        frameStart = SDL_GetTicks();

        // Event polling
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }
            player.handleEvent(e);
        }

        // Calculate the delta time.
        currentTick = SDL_GetTicks();
        float deltaTime = (currentTick - lastTick) / 1000.0f; // Delta time in seconds
        lastTick = currentTick;

        player.update(deltaTime * SPEED); // Update player position

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue background
        SDL_RenderClear(renderer);

        player.render(renderer); // Render player

        // Render the FPS counter
        fpsCounter.update();
        std::stringstream fpsStream;
        fpsStream << "FPS: " << std::fixed << std::setprecision(2) << fpsCounter.getFPS();
        SDL_Surface *fpsSurface = TTF_RenderText_Solid(font, fpsStream.str().c_str(), textColor);
        SDL_Texture *fpsTexture = SDL_CreateTextureFromSurface(renderer, fpsSurface);
        SDL_Rect fpsRect = {10, 10, fpsSurface->w, fpsSurface->h};
        SDL_RenderCopy(renderer, fpsTexture, NULL, &fpsRect);
        SDL_DestroyTexture(fpsTexture);
        SDL_FreeSurface(fpsSurface);

        SDL_RenderPresent(renderer);

        // Cap the frame rate to 180 fps
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < SCREEN_TICK_PER_FRAME) {
            SDL_Delay(SCREEN_TICK_PER_FRAME - frameTime);
        }
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Game closed successfully." << std::endl;
    return 0;
}

