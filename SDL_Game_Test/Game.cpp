#include "Game.h"
#include "AssetManager.h"
#include "SDL.h"
#include "TextureManage.h"
#include "Entity&Component/Components.h"
#include "Vector2D.h"
#include "Map.h"
#include "Collision.h"
#include "sstream"

using namespace std;

SDL_Renderer* Game::renderer = nullptr;
Manager manager;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,1280,720 };

AssetManager* Game::assets = new AssetManager(&manager);

Map* maps;
bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& label(manager.addEntity());

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

	if (TTF_Init() == -1)
	{
		cout << "Error TTF" << endl;
	}

	assets->addTexture("terrain", "resource/mapTile.png");
	assets->addTexture("player", "resource//Prog.png");
	assets->addTexture("projectile", "resource/bullet.png");
	assets->addFont("anders", "resource/Anders.ttf", 24);
	assets->addFont("arial", "resource/arial.ttf", 24);

	maps = new Map("terrain", 3, 32);

	maps->mapLoad("resource/map.map", 40,23);

	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<Control>();
	player.addComponent<Collider>("player");
	player.addGroup(groupPlayers);


	SDL_Color white = { 255,255,255,255 };
	label.addComponent<UILabel>(10, 10, "FontTest", "arial", white);


	assets->createObject(Vector2D(600, 600), Vector2D(2, 0), 200, 2, "projectile");
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectile));

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
	SDL_Rect playerCollider = player.getComponent<Collider>().collide;
	Vector2D playerpos = player.getComponent<TransformComponent>().position;

	stringstream ss;
	ss << "Player: " << playerpos;

	label.getComponent<UILabel>().setLabelText(ss.str(), "arial");

	manager.refresh();
	manager.update();

	for (auto& c : colliders)
	{
		SDL_Rect cCollider = c->getComponent<Collider>().collide;
		if (Collision::isCollide(cCollider, playerCollider))
		{
			player.getComponent<TransformComponent>().position = playerpos;
		}
	}

	for (auto& p : projectiles)
	{
		if (Collision::isCollide(player.getComponent<Collider>().collide, p->getComponent<Collider>().collide))
		{
			p->destroy();
		}
	}

	camera.x = player.getComponent<TransformComponent>().position.x - 640;
	camera.y = player.getComponent<TransformComponent>().position.y - 360;

	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > camera.w)
	{
		camera.x = camera.w;
	}
	if (camera.y > camera.h)
	{
		camera.y = camera.h;
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

	for (auto& c : colliders)
	{
		c->draw();
	}

	for (auto& t : players)
	{
		t->draw();
	}

	for (auto& p : projectiles)
	{
		p->draw();
	}

	label.draw();
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
