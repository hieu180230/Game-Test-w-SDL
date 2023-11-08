#include "Variables.h"
#include "Game.h"

using namespace std;

Game::Game() {};
Game::~Game() {};


void Game::init(const char* title, int xpos, int ypos, int width, int height)
{
	menu_choice = 1;
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
		menu_start = true;

	}
	else 
	{
		menu_start = false;
		isRunning = false;
	}

	if (TTF_Init() == -1)
	{
		cout << "Error TTF" << endl;
	}

	assets->addTexture("player", "resource//ProgTest.png", false);
	assets->addTexture("projectile", "resource/bullet.png", false);
	assets->addTexture("button1", "resource/gui/buttons.png", false);
	assets->addFont("anders", "resource/Anders.ttf", 24);
	assets->addFont("arial", "resource/arial.ttf", 24);
	assets->addFont("comic", "resource/comic.ttf", 24);

	mapsBelow = new Map(assets, 1, 32, "below");
	mapsBelow->mapLoad("resource/map/belowMap.xml", 40,23);
	mapsBelow->interactiveMapLoad("resource/interactiveBlock.map", 40, 23, 1);

	mapsAbove = new Map(assets, 1, 32, "above");
	mapsAbove->mapLoad("resource/map/aboveMap.xml", 40, 23);


	player.addComponent<TransformComponent>(1);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<Control>();
	player.addComponent<Collider>("player");
	player.addGroup(groupPlayers);

	button.addComponent<TransformComponent>(100, 100, 32, 48, 3);
	button.addComponent<Button>("button1");
	button.addGroup(Game::groupButtons);

	SDL_Color white = { 255,255,255,255 };
	SDL_Color black = { 0,0,0,255 };
	label.addComponent<UILabel>(100, 100, "FontTest", "comic", black);
	label.getComponent<UILabel>().setLabelText("ss.str()", "comic");

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

	stringstream ss;
	int playerZ = 1;

	Vector2D PlayerPos = player.getComponent<TransformComponent>().position;
	ss << "Player: " << PlayerPos;

	manager.refresh();
	manager.update();
	//collide handle
	Collision::collisionResolve(player, colliders);
	if (Activation::activationResolve(player, activatersUp, activatersDown, activatersCheck, playerZ))
	{
		mapsBelow->interactiveMapUnload(colliders, activatersUp, activatersDown, activatersCheck);
		mapsBelow->interactiveMapLoad("resource/interactiveBlock.map", 40, 23, playerZ);
	}

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

	camera.x = player.getComponent<TransformComponent>().position.x - WIDTH/2;
	camera.y = player.getComponent<TransformComponent>().position.y - HEIGHT/2;

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
	for (auto& t : tilesBelow)
	{
		t->draw();
	}
	for (auto& t : players)
	{
		t->draw();
	}
	for (auto& t : tilesAbove)
	{
		t->draw();
	}
	for (auto& c : colliders)
	{
		c->draw();
	}
	for (auto& p : projectiles)
	{
		p->draw();
	}

	for (auto& a : activatersUp)
	{
		a->draw();
	}
	for (auto& a : activatersDown)
	{
		a->draw();
	}
	for (auto& a : activatersCheck)
	{
		a->draw();
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


bool Game::running()
{
	return isRunning;
}

void Game::menu_handleEvent()
{
	SDL_PollEvent(&Game::event);
	switch (Game::event.type)
	{
	case SDL_KEYUP:
	{
		menu_choice = (menu_choice == 1 ? 3 : (menu_choice - 1));
		break;
	}
	case SDL_KEYDOWN:
	{
		menu_choice = (menu_choice == 3 ? 1 : (menu_choice + 1));
		break;
	}
	case SDL_QUIT:
	{
		menu_start = false;
		isRunning = false;
		break;
	}
	}
}

void Game::menu_update()
{
	manager.refresh();
	manager.update();
}

void Game::menu_render()
{
	SDL_RenderClear(renderer);
	for (auto& b : buttons)
	{
		b->draw();
	}
	label.draw();
	SDL_RenderPresent(renderer);
}