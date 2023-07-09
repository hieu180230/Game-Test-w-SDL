#include "AssetManager.h"
#include "Entity&Component/Components.h"
AssetManager::AssetManager(Manager* man) : manager(man)
{}

AssetManager::~AssetManager()
{}

map<string, SDL_Texture*> AssetManager::getTextureMap()
{
	return mapTextures;
}

void  AssetManager::createObject(Vector2D pos, Vector2D vel, int range, int speed, string id)
{
	auto& projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
	projectile.addComponent<SpriteComponent>(id, false);
	projectile.addComponent<Projectile>(range, speed, vel);
	projectile.addComponent<Collider>("projectile");
	projectile.addGroup(Game::groupProjectile);
}



void AssetManager::addTexture(string id, const char* path, bool isMap)
{
	if(!isMap) textures.emplace(id, TextureManage::LoadTexture(path));
	if (isMap) mapTextures.emplace(id, TextureManage::LoadTexture(path));
}

void AssetManager::addTextureId(int fid, int lid)
{
	textureId.emplace(fid, lid);
}

SDL_Texture* AssetManager::getTexture(string id)
{
	return textures[id];
}

int AssetManager::getTextureLastId(int fid)
{
	return textureId[fid];
}

void AssetManager::addFont(string id, string path, int fontSize)
{
	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}

TTF_Font* AssetManager::getFont(string id)
{
	return fonts[id];
}
