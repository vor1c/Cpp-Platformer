//
// Created by voric on 19.12.2023.
//
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(SDL_Renderer* renderer, int x, int y) : renderer(renderer) {
    box.x = x;
    box.y = y;
    box.w = 50; // Width of the enemy
    box.h = 50; // Height of the enemy
}

void Enemy::update(const Player& player) {
    followPlayer(player);
}

void Enemy::render() {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green color for the enemy
    SDL_RenderFillRect(renderer, &box);
}

void Enemy::followPlayer(const Player& player) {
    // Simple logic to move towards the player
    if (player.getX() > box.x) box.x++;
    else if (player.getX() < box.x) box.x--;

    if (player.getY() > box.y) box.y++;
    else if (player.getY() < box.y) box.y--;
}
