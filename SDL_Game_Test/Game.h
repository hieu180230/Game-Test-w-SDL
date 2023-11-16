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
	
	SDL_Window* window;
	static SDL_Rect camera;
	static AssetManager* assets;

	static bool isRunning;
	
	Game();
	~Game();
	void init();

	void handleEvent();
	void update();
	void render();
	void clean();
	bool running();

	
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

