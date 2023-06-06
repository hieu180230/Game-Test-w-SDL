#include "Game.h"
#include "SDL.h"
#include "TextureManage.h"
#include "Entity&Component/Components.h"
#include "Vector2D.h"
#include "Map.h"
#include "Collision.h"

using namespace std;

SDL_Renderer* Game::renderer = nullptr;
Manager manager;
SDL_Event Game::event;
Map* map;

vector<Collider*> Game::colliders;

auto& person(manager.addEntity());
auto& wall(manager.addEntity());

auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());

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

	map = new Map();

	tile0.addComponent<TileComponent>(200, 200, 32, 32, 0);
	tile0.addComponent<Collider>("dirt");
	tile1.addComponent<TileComponent>(250, 250, 32, 32, 1);
	tile1.addComponent<Collider>("water");
	tile2.addComponent<TileComponent>(150, 150, 32, 32, 2);
	tile2.addComponent<Collider>("grass");

	person.addComponent<TransformComponent>(2);
	person.addComponent<SpriteComponent>("resource//person.png");
	person.addComponent<Control>();
	person.addComponent<Collider>("player");

	wall.addComponent<TransformComponent>(300.0, 300.0, 20, 20, 1);
	wall.addComponent<SpriteComponent>("resource//water.png");
	wall.addComponent<Collider>("wall");
}


void Game::handleEvent()
{

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

	for (auto c : colliders)
	{
		Collision::isCollide(person.getComponent<Collider>(), *c);
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	// add texture
	map->drawMap();
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
