#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "CPU.h"
#include "Memory.h"
#include "PPU.h"

void drawScreen(SDL_Renderer *renderer, const uint8_t *screenData);

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("NES Emulator",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    PPU ppu;
    Memory memory(ppu);

    // Load a program into memory (for now, we'll just use a dummy program)
    uint8_t program[] = {0xA9, 0x01, 0xAA, 0xE8, 0x00}; // Example program
    for (size_t i = 0; i < sizeof(program); ++i)
    {
        memory.write(0xC000 + i, program[i]);
    }

    CPU cpu(memory);
    cpu.reset();

    bool running = true;
    SDL_Event e;

    while (running)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    running = false;
                    break;
                case SDLK_z: // A button
                    // Handle A button press
                    break;
                case SDLK_x: // B button
                    // Handle B button press
                    break;
                case SDLK_RETURN: // Start button
                    // Handle Start button press
                    break;
                case SDLK_RSHIFT: // Select button
                    // Handle Select button press
                    break;
                case SDLK_UP:
                    // Handle Up button press
                    break;
                case SDLK_DOWN:
                    // Handle Down button press
                    break;
                case SDLK_LEFT:
                    // Handle Left button press
                    break;
                case SDLK_RIGHT:
                    // Handle Right button press
                    break;
                default:
                    break;
                }
            }
            else if (e.type == SDL_KEYUP)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_z: // A button
                    // Handle A button release
                    break;
                case SDLK_x: // B button
                    // Handle B button release
                    break;
                // Handle other button releases...
                default:
                    break;
                }
            }
        }

        cpu.executeInstruction();

        uint8_t screenData[SCREEN_WIDTH * SCREEN_HEIGHT];
        ppu.render(screenData);
        drawScreen(renderer, screenData);

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Simulate ~60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void drawScreen(SDL_Renderer *renderer, const uint8_t *screenData)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int y = 0; y < SCREEN_HEIGHT; ++y)
    {
        for (int x = 0; x < SCREEN_WIDTH; ++x)
        {
            uint8_t color = screenData[y * SCREEN_WIDTH + x];
            SDL_SetRenderDrawColor(renderer, color, color, color, 255);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}
