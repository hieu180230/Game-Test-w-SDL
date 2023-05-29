#include "SDL.h"
#include <iostream>
#include <Windows.h>

using namespace std;

int main(int argc, char* argv[])
{
    const int WIDTH = 640;
    const int HEIGHT = 480;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    bool isRunning = true;
    while (isRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) isRunning = false;
            if (event.type == SDL_MOUSEMOTION)
            {
                cout << "Mouse moved\n";
            }
            if (event.type == SDL_KEYDOWN)
            {
                cout << "Pressed\n";
                if (event.key.keysym.sym == SDLK_0)
                {
                    cout << "0 pressed\n";
                }
            }
            if (event.type == SDL_KEYUP)
            {
                cout << "Released\n";
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}