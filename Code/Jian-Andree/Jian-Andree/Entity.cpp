//Entity.cpp

#include "stdafx.h"

#include "Entity.h"

Entity::Entity()
{

}

Entity::Entity(Vector2 entity_position, int entity_width, int entity_height)
{
}

void Entity::Init(std::string object_type)
{

}

void Entity::Update(float deltatime)
{
	/*
		update object here, movement etc
	*/
}

std::string Entity::getID()
{
	return entity_ID;
}

void Entity::setID(std::string new_ID)
{
	entity_ID = new_ID;
}