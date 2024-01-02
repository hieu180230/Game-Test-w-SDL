#pragma once
#include <SDL.h>
#include "SDL_image.h"
#include "./glad/glad.h"
#include <iostream>
#include <vector>
#include "Game.h"
#include "AssetManager.h"
#include "./Entity&Component/Components.h"

using namespace std;
class AssetManager;


class Menu {
public:
	SDL_Point mousePosition;
	SDL_Window* window;
	int menu_choice = 1;
	inline static bool menu_start = false;

	Menu() {};
	~Menu() {};
	void init(const char* title, int xpos, int ypos, int width, int height);
	
	
	void handleEvent();
	void update();
	void render();
	bool running() { return menu_start; }

	void showSetting();
};