#include "Menu.h"
extern Manager manager;
auto& buttons(manager.getGroup(Game::groupButtons));
auto& button1(manager.addEntity());
auto& button2(manager.addEntity());

void Menu::init(const char* title, int xpos, int ypos, int width, int height)
{
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
		if (window)
		{
			cout << "Window init!" << endl;
		}
		Game::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (Game::renderer)
		{
			SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
			cout << "Renderer init!" << endl;
		}
		Game::isRunning = true;
		menu_start = true;

	}
	else
	{
		menu_start = false;
		Game::isRunning = false;
	}
	menu_choice = 1;
	Game::assets->addTexture("button1", "resource/gui/buttons.png", false);

	Game::assets->addFont("anders", "resource/Anders.ttf", 24);
	Game::assets->addFont("arial", "resource/arial.ttf", 24);
	Game::assets->addFont("comic", "resource/comic.ttf", 24);
	
	button1.addComponent<TransformComponent>(280, 100, 32, 48, 2);
	button1.addComponent<Button>("button1");
	button1.addGroup(Game::groupButtons);

	button1.addComponent<TransformComponent>(280, 200, 32, 48, 2);
	button1.addComponent<Button>("button1");
	button1.addGroup(Game::groupButtons);
}

void Menu::handleEvent()
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
		Game::isRunning = false;
		break;
	}
	}
}

void Menu::update()
{
	manager.refresh();
	manager.update();
}

void Menu::render()
{
	SDL_RenderClear(Game::renderer);
	for (auto& b : buttons)
	{
		b->draw();
	}
	SDL_RenderPresent(Game::renderer);
}