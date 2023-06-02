#include "Object.h"
#include "textureManage.h"

Object::Object(const char* text, int xpos, int ypos) 
{
	texture = TextureManage::LoadTexture(text);

	x = xpos;
	y = ypos;
};
Object::~Object() {};

int Object::getX()
{
	return x;
}
void Object::setX(int x)
{
	this->x = x;
}
int Object::getY()
{
	return y;
}
void Object::setY(int y)
{
	this->y = y;
}

void Object::Update()
{

	srcR.h = 32;
	srcR.w = 32;
	srcR.x = 0;
	srcR.y = 0;

	destR.x = x;
	destR.y = y;
	destR.h = srcR.h * 2;
	destR.w = srcR.w * 2;
}

void Object::Render()
{
	SDL_RenderCopy(Game::renderer, texture, &srcR, &destR);

}
