#include "Game.h"
#include "SDL.h"
#include "TextureManage.h"
#include "Entity&Component/Components.h"
#include "Vector2D.h"

using namespace std;

SDL_Renderer* Game::renderer = nullptr;
Manager manager;
auto& person(manager.addEntity());


int step = 0, jump = ground;

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

	person.addComponent<TransformComponent>();
	person.addComponent<SpriteComponent>("resource//person.png");

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
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();
	person.getComponent<TransformComponent>().position.Add(Vector2D(5, 3.5));
	cout << person.getComponent<TransformComponent>().position;
	if (person.getComponent<TransformComponent>().position.x == 640 && person.getComponent<TransformComponent>().position.y == 448)
	{
		person.getComponent<TransformComponent>().position.x = 0.0;
		person.getComponent<TransformComponent>().position.y = 0.0;
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	// add texture
	manager.draw();
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
