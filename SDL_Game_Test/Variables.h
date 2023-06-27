#pragma once
#include "SDL.h"
#include "TextureManage.h"
#include "Entity&Component/Components.h"
#include "Vector2D.h"
#include "Map.h"
#include "Collision.h"
#include <vector>
#include "sstream"

float gravAccel = 0.25;
float gravMax = 1.5;
bool grounded = false;

Manager manager;
Map* maps;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0,0,640,480 };
AssetManager* Game::assets = new AssetManager(&manager);
bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& label(manager.addEntity());

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectile));
auto& activaters(manager.getGroup(Game::groupActivate));