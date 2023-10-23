#include "Menu.h"

Menu::Menu() {}
Menu::~Menu(){}

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

	}
	else Game::isRunning = false;
}

void Menu::handleEvent()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_KEYUP:
	{
		choice = (choice == 1 ? 3 : (choice + 1));
		break;
	}
	case SDL_KEYDOWN:
	{
		choice = (choice == 3 ? 1 : (choice - 1));
		break;
	}
	case SDL_QUIT:
	{
		Game::isRunning = false;
		break;
	}
	}
}