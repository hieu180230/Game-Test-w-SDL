#pragma once
#include <SDL.h>
#include <string>
#include "Entity&Component/Entity&Component.h"

class Activater;

class Activation
{
public:
	static bool activationResolve(Entity& player, vector<Entity*> activatersUp, vector<Entity*> activatersDown, vector<Entity*> activatersCheck, int& z);
};