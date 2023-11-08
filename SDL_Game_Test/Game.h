#pragma once
#include <SDL.h>
#include "SDL_image.h"
#include "./glad/glad.h"
#include <iostream>
#include <vector>


#define ground 320
using namespace std;

const int WIDTH = 640;
const int HEIGHT = 480;

class Collider;
class AssetManager;

class Game
{

public:
	int menu_choice = 1;
	SDL_Window* window;
	static SDL_Rect camera;
	static AssetManager* assets;

	static bool isRunning;
	inline static bool menu_start = false;
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height);

	void handleEvent();
	void update();
	void render();
	void clean();
	bool running();

	void menu_handleEvent();
	void menu_update();
	void menu_render();
	bool menu_running() { return menu_start; }


	static SDL_Renderer* renderer;
	static SDL_Event event;

	enum groupLabel : size_t
	{
		groupMapAbove,
		groupPlayers,
		groupColliders,
		groupActivateUp,
		groupActivateDown,
		groupActivateCheck,
		groupProjectile,
		groupMapBelow,
		groupButtons
	};


};

