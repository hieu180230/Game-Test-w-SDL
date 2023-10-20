#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "glad/include/glad/glad.h"
#include <iostream>
#include <vector>
#include "Game.h"

//NoesisGUI include
#include <NsCore/Noesis.h>
#include <NsCore/Log.h>
#include <NsCore/Hash.h>
#include <NsRender/Texture.h>
#include <NsRender/RenderTarget.h>
#include <NsGui/TextureProvider.h>
using namespace Noesis;
//end of NoesisGUI include

class Menu
{
private:
	SDL_Window* window;
	int choice = 1;
	SDL_Event event;
public:
	Menu();
	~Menu();

	void init(const char* title, int xpos, int ypos, int width, int height);
	void handleEvent();
	void update();
	void render();

};