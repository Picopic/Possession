//StaticObject.h

#pragma once

//Base class
#include "Entity.h"

class StaticObject : public Entity
{
public:
	//Constructor that takes care of simple initialisation
	StaticObject();
	//Constructor that takes care of some more essential initialisation
	StaticObject(ConfigManager* ConfigMgr, Vector2 Position, std::string Object);

	//Initialise some basic variables
	void Init(std::string Object, Alignment ObjectAlignment, Type ObjectType);
	
	//Update the Entity
	void Update(float Deltatime);

	//Collision updates
	void OnCollision(Entity* CollisionEntity,Type CollisionType, Vector2 Offset, Alignment EnemyAlignment);

private:
};