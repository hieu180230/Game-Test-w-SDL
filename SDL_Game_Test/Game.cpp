#include "Game.h"
#include "SDL.h"
using namespace std;

SDL_Texture* person, *crouch_person;
SDL_Rect srcR, destR;

int step = 0, jump = ground;
bool crouch = false;

Game::Game() {};
Game::~Game() {};

void Game::init(const char* title, int xpos, int ypos, int width, int height)
{
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
		if (window)
		{
			cout << "Window init!" << endl;
		}
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			cout << "Renderer init!" << endl;
		}
		isRunning = true;

	}
	else isRunning = false;
	SDL_Surface* surface = IMG_Load("resource//person.png");
	person = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("resource//crouch_person.png");
	crouch_person = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

void Game::handleEvent()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
	{
		isRunning = false;
		break;
	}
	case SDL_KEYDOWN:
	{
		const Uint8* state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_RIGHT]) step += 4;
		if (state[SDL_SCANCODE_LEFT]) step -= 4;
		if (state[SDL_SCANCODE_DOWN])
		{
			crouch = true;
		}
		if (state[SDL_SCANCODE_UP])
		{
			if (crouch == true)
			{
				crouch = false;
				break;
			}
		}
		break;
	}
	}
}

void Game::update()
{
	count++;
	destR.h = 64;
	destR.w = 64;
	destR.y = jump;
	destR.x = step;
	if (step > 640)
	{
		step = -10;
	}
	if (step < -10)
	{
		step = 640;
	}

	cout << count << endl;
}

void Game::render()
{
	int crouchtime = 0;
	SDL_RenderClear(renderer);
	// add texture
	if (crouch == true) {
		SDL_RenderCopy(renderer, crouch_person, NULL, &destR); 
	}
	else SDL_RenderCopy(renderer, person, NULL, &destR);
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
	cout << "System cleaned!" << endl;
}

bool Game::running()
{
	return isRunning;
}
