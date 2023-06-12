#include "../include/SoftwareRasterizer.h"
#include <iostream>


SoftwareRasterizer *softwareRasterizer = nullptr;
int main(){

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    softwareRasterizer = new SoftwareRasterizer();
    softwareRasterizer->init();
    
    
    while (softwareRasterizer->running())
    {   
        frameStart = SDL_GetTicks();
        softwareRasterizer->handleEvents();
        softwareRasterizer->update();
        softwareRasterizer->render();
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    softwareRasterizer->saveFramebuffer();
    softwareRasterizer->clean();
    return 0;
}