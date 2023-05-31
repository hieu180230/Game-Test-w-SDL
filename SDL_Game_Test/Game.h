#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "glad/include/glad/glad.h"
#include <iostream>
using namespace std;

const int WIDTH = 640;
const int HEIGHT = 480;

class Game
{
private:
	int count = 0;
	bool isRunning = false;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
public:
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height);

	void handleEvent();
	void update();
	void render();
	void clean();

	bool running();
};

