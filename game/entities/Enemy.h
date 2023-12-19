//
// Created by voric on 19.12.2023.
//

#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>
#include "Player.h" // Make sure this includes your Player class

class Enemy {
public:
    Enemy(SDL_Renderer* renderer, int x, int y);
    void update(const Player& player);
    void render();

private:
    SDL_Renderer* renderer;
    SDL_Rect box; // The enemy's position and size

    // Function to update enemy's position
    void followPlayer(const Player& player);
};

#endif // ENEMY_H


