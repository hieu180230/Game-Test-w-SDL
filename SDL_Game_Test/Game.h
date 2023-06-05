#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "glad/include/glad/glad.h"
#include <iostream>
#define ground 320
using namespace std;

const int WIDTH = 640;
const int HEIGHT = 480;

class Game
{
private:
	bool isRunning = false;
	SDL_Window* window = NULL;


public:
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height);

	void handleEvent();
	void update();
	void render();
	void clean();
	bool running();

	static SDL_Renderer* renderer;
	static SDL_Event event;
};

