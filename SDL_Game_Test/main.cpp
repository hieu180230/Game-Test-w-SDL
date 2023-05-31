#include "Game.h"

using namespace std;


Game game;

void setPixel(SDL_Surface* screen, int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
    SDL_LockSurface(screen);
    SDL_Log("%d %d", x, y);
    uint8_t* pixelArray = (uint8_t*)screen->pixels;
    pixelArray[y * screen->pitch + x * screen->format->BytesPerPixel + 0] = b;
    pixelArray[y * screen->pitch + x * screen->format->BytesPerPixel + 1] = g;
    pixelArray[y * screen->pitch + x * screen->format->BytesPerPixel + 2] = r; // It is RGB but it also comes in BGR
    SDL_UnlockSurface(screen);
}

int main(int argc, char* argv[])
{
    game.init("Testing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT);
    while (game.running())
    {
        game.handleEvent();
        game.update();
        game.render();

    }

    game.clean();
    /*SDL_Surface* screen; //window surface
    SDL_Surface* image; //load image

    SDL_Init(SDL_INIT_VIDEO);
    //Open GL init
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


    window = SDL_CreateWindow("Testing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    screen = SDL_GetWindowSurface(window);
    image = SDL_LoadBMP("resource//cat-owl.bmp");

    //create a rect
    SDL_Rect rectangle;
    rectangle.x = 50;
    rectangle.y = 75;
    rectangle.w = 200;
    rectangle.h = 200;
    SDL_Rect rectangle2;
    rectangle2.x = 50;
    rectangle2.y = 75;
    rectangle2.w = 200;
    rectangle2.h = 200;
    
    //cope a texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
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
        //retrieve mouse cord
        int x, y;
        Uint32 button;
        button = SDL_GetMouseState(&x, &y);
        
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) isRunning = false;
            if (event.type == SDL_MOUSEMOTION)
            {
                rectangle2.x = event.motion.x;
                rectangle2.y = event.motion.y;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_ADD);
                }
                if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
                }
                if (event.button.button == SDL_BUTTON_MIDDLE)
                {
                    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_MOD);
                }
            }
            else
            {
                SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
            }
        }
        //draw sth
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &rectangle);
        SDL_RenderCopy(renderer, texture, NULL, &rectangle2);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();*/
    return 0;
}