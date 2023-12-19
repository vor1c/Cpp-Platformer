#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>

class Player {
public:
    Player(int x, int y, int width, int height, int screen_width, int screen_height);
    void handleEvent(SDL_Event& e);
    void update(float deltaTime);
    void render(SDL_Renderer* renderer) const;
    void clampPosition();

private:
    SDL_Rect mRect;
    int mVelX, mVelY;
    int mScreenWidth, mScreenHeight;
    const int SPEED = 5;
};

#endif // PLAYER_H
