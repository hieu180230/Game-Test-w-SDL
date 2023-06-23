#include "Variables.h"

using namespace std;

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
	assets->addTexture("player", "resource//ProgTest.png");
	assets->addTexture("projectile", "resource/bullet.png");
	assets->addFont("anders", "resource/Anders.ttf", 24);
	assets->addFont("arial", "resource/arial.ttf", 24);

	maps = new Map("terrain", 1, 32);
	maps->mapLoad("resource/map.map", 40,23);

	player.addComponent<TransformComponent>(1);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<Control>();
	player.addComponent<Collider>("player");
	player.addGroup(groupPlayers);


	SDL_Color white = { 255,255,255,255 };
	label.addComponent<UILabel>(10, 10, "FontTest", "arial", white);

	//assets->createObject(Vector2D(600, 600), Vector2D(2, 0), 200, 2, "projectile");
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
	grounded = false;
	stringstream ss;
	Vector2D PlayerPos = player.getComponent<TransformComponent>().position;


	ss << "Player: " << PlayerPos;
	label.getComponent<UILabel>().setLabelText(ss.str(), "arial");

	manager.refresh();
	manager.update();
	/*
	SDL_Rect playerCollider = player.getComponent<Collider>().collide;
	
	for (auto& c : colliders)
	{
		SDL_Rect cCollider = c->getComponent<Collider>().collide;
		if (Collision::isCollide(playerCollider, cCollider))
		{
			player.getComponent<TransformComponent>().position = PlayerPos;
		}
	}*/

	SDL_Rect playerCollider = player.getComponent<Collider>().collide;

	bool canMoveX = true;
	bool canMoveY = true;

	for (auto& c : colliders)
	{
		SDL_Rect cCollider = c->getComponent<Collider>().collide;

		// Check for collision in the x-axis
		SDL_Rect xCheckCollider = playerCollider;
		xCheckCollider.x += player.getComponent<TransformComponent>().velocity.x;

		if (Collision::isCollide(xCheckCollider, cCollider))
		{
			canMoveX = false;
		}

		// Check for collision in the y-axis
		SDL_Rect yCheckCollider = playerCollider;
		yCheckCollider.y += player.getComponent<TransformComponent>().velocity.y;

		if (Collision::isCollide(yCheckCollider, cCollider))
		{
			canMoveY = false;
			grounded = true;
		}

		// If both axes have collision, exit the loop
		if (!canMoveX && !canMoveY)
		{
			break;
		}
	}

	if (!canMoveX) player.getComponent<TransformComponent>().velocity.x = 0;
	if (!canMoveY) player.getComponent<TransformComponent>().velocity.y = 0;

	/*for (auto& p : projectiles)
	{
		if (Collision::isCollide(player.getComponent<Collider>().collide, p->getComponent<Collider>().collide))
		{
			p->destroy();
		}
	}*/


	if (player.getComponent<TransformComponent>().position.x > 2550) player.getComponent<TransformComponent>().position.x = -60;
	if (player.getComponent<TransformComponent>().position.x < -60) player.getComponent<TransformComponent>().position.x = 2550;
	if (player.getComponent<TransformComponent>().position.y > 1430) player.getComponent<TransformComponent>().position.y = -60;
	if (player.getComponent<TransformComponent>().position.y < -60) player.getComponent<TransformComponent>().position.y = 1430;

	camera.x = player.getComponent<TransformComponent>().position.x - 320;
	camera.y = player.getComponent<TransformComponent>().position.y - 240;

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
