#include "Variables.h"

using namespace std;

Game::Game() {};
Game::~Game() {};


void Game::init()
{
	
	if (TTF_Init() == -1)
	{
		cout << "Error TTF" << endl;
	}

	assets->addTexture("player", "resource//ProgTest.png", false);
	assets->addTexture("projectile", "resource/bullet.png", false);
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


	SDL_Color white = { 255,255,255,255 };
	label.addComponent<UILabel>(100, 100, "FontTest", "comic", white);
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
