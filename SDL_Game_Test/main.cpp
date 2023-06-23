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




/*/
#include "SDL.h"
#include <math.h>
#include <utility>
using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int SQUARE_SIZE = 50;
const int SQUARE_VELOCITY = 1;

bool checkCollision(SDL_Rect square1, SDL_Rect square2) {
    if (square1.x < square2.x + square2.w &&
        square1.x + square1.w > square2.x &&
        square1.y < square2.y + square2.h &&
        square1.y + square1.h > square2.y) {
        return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Collision Detection", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Square position variables
    int squareX = WINDOW_WIDTH / 2 - SQUARE_SIZE / 2;
    int squareY = WINDOW_HEIGHT / 2 - SQUARE_SIZE / 2;

    // Ground and wall squares
    SDL_Rect groundRect = { 0, WINDOW_HEIGHT - SQUARE_SIZE, WINDOW_WIDTH, SQUARE_SIZE };
    SDL_Rect wallRect = { WINDOW_WIDTH / 2 - SQUARE_SIZE / 2, WINDOW_HEIGHT / 2 - SQUARE_SIZE * 2, SQUARE_SIZE, SQUARE_SIZE * 4 };

    // Game loop
    bool isRunning = true;
    SDL_Event event;
    while (isRunning) {
        // Event handling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw ground
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &groundRect);

        // Draw wall
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &wallRect);

        // Move square with arrow keys
        const Uint8* keystates = SDL_GetKeyboardState(nullptr);
        int deltaX = 0;
        int deltaY = 0;
        if (keystates[SDL_SCANCODE_UP])
            deltaY -= SQUARE_VELOCITY;
        if (keystates[SDL_SCANCODE_DOWN])
            deltaY += SQUARE_VELOCITY;
        if (keystates[SDL_SCANCODE_LEFT])
            deltaX -= SQUARE_VELOCITY;
        if (keystates[SDL_SCANCODE_RIGHT])
            deltaX += SQUARE_VELOCITY;

        // Update square position
        SDL_Rect movingSquareRect = { squareX + deltaX, squareY + deltaY, SQUARE_SIZE, SQUARE_SIZE };

        // Check collision with wall
        if (checkCollision(movingSquareRect, wallRect)) {
            // Resolve collision by adjusting the delta values
            if (deltaX > 0) // Moving right
                deltaX = wallRect.x - (squareX + SQUARE_SIZE);
            else if (deltaX < 0) // Moving left
                deltaX = (wallRect.x + wallRect.w) - squareX;
            if (deltaY > 0) // Moving down
                deltaY = wallRect.y - (squareY + SQUARE_SIZE);
            else if (deltaY < 0) // Moving up
                deltaY = (wallRect.y + wallRect.h) - squareY;
        }

        // Update square position based on resolved delta values
        squareX += deltaX;
        squareY += deltaY;

        // Draw moving square
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect movingSquare = { squareX, squareY, SQUARE_SIZE, SQUARE_SIZE };
        SDL_RenderFillRect(renderer, &movingSquare);

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}*/

