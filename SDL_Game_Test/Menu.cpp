#include "Menu.h"
extern Manager manager;
auto& main_buttons(manager.getGroup(Game::groupMenu));
auto& start_button(manager.addEntity());
auto& setting_button(manager.addEntity());
auto& quit_button(manager.addEntity());

auto& setting_buttons(manager.getGroup(Game::groupSetting));
auto& mute_music(manager.addEntity());
auto& mute_vfx(manager.addEntity());

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
	Game::assets->addTexture("button1", "resource/gui/buttons1.png", false);

	//Game::assets->addFont("anders", "resource/Anders.ttf", 24);
	//Game::assets->addFont("arial", "resource/arial.ttf", 24);
	//Game::assets->addFont("comic", "resource/comic.ttf", 24);
	
	start_button.addComponent<TransformComponent>(280, 100, 64, 96, 1);
	start_button.addComponent<Button>("button1", 0);
	start_button.addGroup(Game::groupMenu);

	setting_button.addComponent<TransformComponent>(280, 200, 64, 96, 1);
	setting_button.addComponent<Button>("button1", 1);
	setting_button.addGroup(Game::groupMenu);

	quit_button.addComponent<TransformComponent>(280, 300, 64, 96, 1);
	quit_button.addComponent<Button>("button1", 2);
	quit_button.addGroup(Game::groupMenu);

	
}

void Menu::handleEvent()
{
	SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
	SDL_PollEvent(&Game::event);
	switch (Game::event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
	{
		if (Game::event.button.button == SDL_BUTTON_LEFT)
		{
			if (SDL_PointInRect(&mousePosition, start_button.getComponent<Button>().getRect()))
			{
				start_button.getComponent<Button>().clicked(true);
				cout << "Click1" << endl;
				menu_start = false;
			}
			else if (SDL_PointInRect(&mousePosition, setting_button.getComponent<Button>().getRect()))
			{
				setting_button.getComponent<Button>().clicked(true);
				cout << "Click2" << endl;
			}
			else if (SDL_PointInRect(&mousePosition, quit_button.getComponent<Button>().getRect()))
			{
				quit_button.getComponent<Button>().clicked(true);
				cout << "Click3" << endl;
				menu_start = false;
				Game::isRunning = false;
			}
		}
		break;
	}
	case SDL_MOUSEBUTTONUP:
	{
		if (Game::event.button.button == SDL_BUTTON_LEFT)
		{
			for (auto& b : main_buttons)
			{
				b->getComponent<Button>().clicked(false);
			}
		}
		break;
	}
	case SDL_KEYDOWN:
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_UP:  menu_choice = (menu_choice == 1 ? 3 : (menu_choice - 1)); break;
		case SDLK_DOWN: menu_choice = menu_choice = (menu_choice == 3 ? 1 : (menu_choice + 1)); break;
		}
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
	for (auto& b : main_buttons)
	{
		b->draw();
	}
	SDL_RenderPresent(Game::renderer);
}



void showSetting()
{
	
}