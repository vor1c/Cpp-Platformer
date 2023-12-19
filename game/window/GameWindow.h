#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SDL.h>

class GameWindow {
public:
    GameWindow();
    ~GameWindow();

    bool init(bool fullscreen);
    void close();
    SDL_Renderer* getRenderer() const;

    int getWidth() const; // Add this line
    int getHeight() const; // And this line

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif // GAMEWINDOW_H
