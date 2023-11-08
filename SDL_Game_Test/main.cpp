#include "Game.h"
using namespace std;


Game game;


int main(int argc, char* argv[])
{
    //Limit framerate
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;
    game.init("Testing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT);
    while (game.menu_running())
    {
        frameStart = SDL_GetTicks();

        game.menu_handleEvent();
        game.menu_update();
        game.menu_render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    
    while (game.running())
    {
        frameStart = SDL_GetTicks();

        game.handleEvent();
        game.update();
        game.render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game.clean();
    return 0;
}






