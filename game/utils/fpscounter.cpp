//
// Created by voric on 14.12.2023.
//
#include "FPSCounter.h"

FPSCounter::FPSCounter() {
    startTime = SDL_GetTicks();
    frameCount = 0;
    fps = 0.0;
}

FPSCounter::~FPSCounter() {}

void FPSCounter::start() {
    startTime = SDL_GetTicks();
    frameCount = 0;
    fps = 0.0;
}

void FPSCounter::update() {
    Uint32 currentTime = SDL_GetTicks();
    Uint32 deltaTime = currentTime - startTime;
    frameCount++;

    if (deltaTime >= 1000) {
        fps = static_cast<double>(frameCount) / (deltaTime / 1000.0);
        frameCount = 0;
        startTime = currentTime;
    }
}

double FPSCounter::getFPS() const {
    return fps;
}
