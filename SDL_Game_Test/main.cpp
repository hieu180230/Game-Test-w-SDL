#include "SDL.h"
#include "glad/include/glad/glad.h"
#include <iostream>
#include <Windows.h>

using namespace std;

int main(int argc, char* argv[])
{
    const int WIDTH = 640;
    const int HEIGHT = 480;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Surface* screen; //window surface
    SDL_Surface* image; //load image

    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


    window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    screen = SDL_GetWindowSurface(window);
    image = SDL_LoadBMP("resource//cat-owl.bmp");
    SDL_BlitSurface(image, NULL, screen, NULL);
    SDL_FreeSurface(image);

    SDL_GLContext context;
    context = SDL_GL_CreateContext(window);

    gladLoadGLLoader(SDL_GL_GetProcAddress);

    //update window
    SDL_UpdateWindowSurface(window);

    const Uint8* state = SDL_GetKeyboardState(NULL);
    bool isRunning = true;
    while (isRunning)
    {
        glViewport(0, 0, WIDTH, HEIGHT);

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) isRunning = false;
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                SDL_LockSurface(screen);
                SDL_memset(screen->pixels, 255, screen->h * screen->pitch);
                SDL_UnlockSurface(screen);
                SDL_UpdateWindowSurface(window);
            }
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}