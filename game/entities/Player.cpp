#include "Player.h"

Player::Player(int x, int y, int width, int height, int screen_width, int screen_height)
        : mRect{x, y, width, height}, mVelX(0), mVelY(0), mScreenWidth(screen_width), mScreenHeight(screen_height) {
}

void Player::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_w: mVelY -= SPEED; break;
            case SDLK_s: mVelY += SPEED; break;
            case SDLK_a: mVelX -= SPEED; break;
            case SDLK_d: mVelX += SPEED; break;
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_w: mVelY += SPEED; break;
            case SDLK_s: mVelY -= SPEED; break;
            case SDLK_a: mVelX += SPEED; break;
            case SDLK_d: mVelX -= SPEED; break;
        }
    }
}

int Player::getX() const {
    return mRect.x;
}

int Player::getY() const {
    return mRect.y;
}


void Player::update(float deltaTime) {
    mRect.x += static_cast<int>(mVelX * deltaTime);
    mRect.y += static_cast<int>(mVelY * deltaTime);
    clampPosition();
}

void Player::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set draw color to red
    SDL_RenderFillRect(renderer, &mRect);
}

void Player::clampPosition() {
    // Clamp the position of the player to stay within the screen bounds
    if (mRect.x < 0) {
        mRect.x = 0;
    } else if (mRect.x + mRect.w > mScreenWidth) {
        mRect.x = mScreenWidth - mRect.w;
    }

    if (mRect.y < 0) {
        mRect.y = 0;
    } else if (mRect.y + mRect.h > mScreenHeight) {
        mRect.y = mScreenHeight - mRect.h;
    }
}
