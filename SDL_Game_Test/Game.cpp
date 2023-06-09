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
Map* maps;
bool Game::isRunning = false;

vector<Collider*> Game::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());
const char* mapFile = "resource//mapTile.png";

enum groupLabel : size_t
{
	groupMap,
	groupPlayers,
	groupColliders
};

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));

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

	maps = new Map();

	Map::mapLoad("resource/map.map", 40,23);

	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("resource//Prog.png", true);
	player.addComponent<Control>();
	player.addComponent<Collider>("player");
	player.addGroup(groupPlayers);

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

	Vector2D pVel = player.getComponent<TransformComponent>().velocity;
	int pSpeed = player.getComponent<TransformComponent>().speed;
	
	for (auto t : tiles)
	{
		t->getComponent<TileComponent>().destR.x += -(pVel.x * pSpeed);
		t->getComponent<TileComponent>().destR.y += -(pVel.y * pSpeed);
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	// add texture
	for (auto& t : tiles)
	{
		t->draw();
	}
	for (auto& t : players)
	{
		t->draw();
	}
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

void Game::addTile(int srcX, int srcY, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, x, y, mapFile);
	tile.addGroup(groupMap);
}

bool Game::running()
{
	return isRunning;
}
