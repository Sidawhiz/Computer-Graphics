#pragma once
#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
class SoftwareRasterizer
{
public:
    SoftwareRasterizer();
    ~SoftwareRasterizer();

    void init();

    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() { return isRunning; };
    void saveFramebuffer();
    void clearFramebuffer(glm::vec4 colour);

    void rasterTriangle(glm::vec4 vertex1, glm::vec4 vertex2, glm::vec4 vertex3, glm::vec4 colour1, glm::vec4 colour2, glm::vec4 colour3);

    int count = 0;

    void setColor(SDL_Surface* screen,uint8_t r, uint8_t g, uint8_t b);
    void SuperSampling(int i, int j, int width, int height);
    void copyBuffer(SDL_Surface* temp , SDL_Surface* framebuffer);
    void drawLine(glm::vec4 vertex1, glm::vec4 vertex2);
    glm::vec4 interpolateColorOnTriangle(glm::vec4 vertex1, glm::vec4 vertex2, glm::vec4 vertex3, glm::vec4 color1, glm::vec4 color2, glm::vec4 color3, glm::vec4 point);

    // Framebuffer
    const int frameWidth = 80;
    const int frameHeight = 80;

    const int displayScale = 5; // display scaled version of framebuffer so you can see the pixels

    // Output file
    const char* outputFile = "out.png";

    static SDL_Event event;
    static glm::mat4 NDC_to_Screen_Matrix;


private:
    bool isRunning;
    SDL_Window *win;
    SDL_Surface* surface = NULL;
    SDL_Surface* framebuffer = NULL;
    SDL_Surface* temp = NULL;
};

#endif