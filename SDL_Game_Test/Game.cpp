#include "Game.h"
#include "SDL.h"
#include "TextureManage.h"
#include "Object.h"

using namespace std;

SDL_Renderer* Game::renderer = nullptr;

Object *person, *crouch_person;

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
	person = new Object("resource//person.png", 0, 340);
	crouch_person = new Object("resource//crouch_person.png", person->getX(), person->getY());
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
		if (state[SDL_SCANCODE_RIGHT]) step += 2;
		if (state[SDL_SCANCODE_LEFT]) step -= 2;
		if (state[SDL_SCANCODE_DOWN])
		{
			crouch = true;
		}
		break;
	}
	case SDL_KEYUP:
	{
		if (SDLK_DOWN == event.key.keysym.sym)
		{
			crouch = false;
		}
		break;
	}
	}
}

void Game::update()
{
	person->setX(step);
	crouch_person->setX(step);
	person->Update();
	crouch_person->Update();
}

void Game::render()
{
	int crouchtime = 0;
	SDL_RenderClear(renderer);
	// add texture
	if (crouch == true) {
		crouch_person->Render();
	}
	else person->Render();
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
