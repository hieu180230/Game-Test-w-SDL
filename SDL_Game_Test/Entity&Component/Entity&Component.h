#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

using namespace std;

class Component; //multiple components of an entity
class Entity;//mark an entity
class Manager;//store entities

using ComponentID = size_t; // call size_t ComponentID
using Group = size_t;

inline ComponentID getComponentTypeID()
{
	static ComponentID lastID = 0u;//static to remain the value of ID
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept //get id of a specific type of component
{
	static ComponentID typeID{ getComponentTypeID() };
	return typeID;
}

constexpr size_t maxComponents = 32; // constant expression -> be used from compile time -> faster and use less memory: https://learn.microsoft.com/en-us/cpp/cpp/constexpr-cpp?view=msvc-170
constexpr size_t maxGroup = 32;

using ComponentBitSet = bitset<maxComponents>; // bitset = fixed size array of bits
using GroupBitSet = bitset<maxGroup>;
using ComponentArray = array<Component*, maxComponents>; //array of Component* with the size of maxComponents

class Component
{
public:
	Entity* entity;
	
	//these function appear to be override by any type of components of an entity
	virtual void init() {};
	virtual void update() {};
	virtual void draw() {};

	virtual ~Component() {};
};

class Entity // keep list of components
{
private:
	Manager& manager;

	bool active = true;
	vector<unique_ptr<Component>> components; //unique_ptr is for automatic memory management 
	ComponentArray componentArray;//store components of an entity
	ComponentBitSet componentBitset;
	GroupBitSet groupBitSet;

public:

	Entity(Manager& mManager) : manager(mManager) {}
	void update() // update every component in the components array
	{
		for (auto& c : components) c->update();
	}
	void draw() // draw every component
	{
		for (auto& c : components) c->draw();
	}
	bool isActive() { return active; }
	void destroy() { active = false; }

	bool hasGroup(Group mGroup)// check if an entity belong to a group
	{
		return groupBitSet[mGroup];
	}

	void addGroup(Group mGroup); //add an entity to a group
	void delGroup(Group mGroup) // delete an entity from a group
	{
		groupBitSet[mGroup] = false;
	}

	//check if entity has components
	template <typename T> bool hasComponent() const
	{
		return componentBitset[getComponentTypeID<T>()];
	}

	//add a component to an entity
	template <typename T, typename... TArgs> // typename... TArgs means this template can accept more than one argument
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(forward<TArgs>(mArgs)...));//forward mArgs to c
		c->entity = this; //point c's entity too current entity
		unique_ptr<Component> uPtr{ c };//uPtr has Component type and is c
		components.emplace_back(move(uPtr));//move uPtr/c to components vector

		componentArray[getComponentTypeID<T>()] = c; //set an element in componentArray to point to c
		componentBitset[getComponentTypeID<T>()] = true;//set the corresponding position to true

		c->init();//the init function of corresponding subclass
		return *c;
	}

	template<typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]); //retrieve the pointer from the componentArray at index returned from getComponentTypeID function
		return *static_cast<T*>(ptr);//deference and return the pointer
	}
};

//manage multiple entities
class Manager
{
private:
	vector<unique_ptr<Entity>> entities; //store entities
	array<vector<Entity*>, maxGroup> groupEntities; //store entities' group
public:
	//update each entity
	void update()
	{
		for (auto& e : entities) e->update();
	}
	//draw each entity
	void draw()
	{
		for (auto& e : entities) e->draw();
	}


	void refresh()
	{
		//remove an inactive or groupless component of an entity
		for (auto c(0u); c < maxGroup; c++)
		{
			auto& v(groupEntities[c]);
			v.erase(
				remove_if(begin(v), end(v), [c](Entity* mEntity)
					{
						return !mEntity->isActive() || !mEntity->hasGroup(c);
					}),
				end(v));
		}

		//remove an inactive or groupless entity
		entities.erase(remove_if(begin(entities), end(entities), 
			[](const unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}), 
			end(entities));
	}

	//add an entity to a group
	void addToGroup(Entity* mEntity, Group mGroup)
	{
		groupEntities[mGroup].emplace_back(mEntity);
	}

	//get entities of a group
	vector<Entity*>& getGroup(Group mGroup)
	{
		return groupEntities[mGroup];
	}

	//add a new entity
	Entity& addEntity()
	{
		Entity* e = new Entity(*this);
		unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(move(uPtr));
		return *e;
	}
};



