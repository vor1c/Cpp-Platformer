//
// Created by voric on 14.12.2023.
//
#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include <SDL.h>

class FPSCounter {
public:
    FPSCounter();
    ~FPSCounter();

    void start();
    void update();
    double getFPS() const;

private:
    Uint32 startTime;
    Uint32 frameCount;
    double fps;
};

#endif // FPSCOUNTER_H
