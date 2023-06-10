#include "Entity&Component.h"
//add an entity to a group
void Entity::addGroup(Group mGroup)
{
	groupBitSet[mGroup] = true;
	manager.addToGroup(this, mGroup);
}