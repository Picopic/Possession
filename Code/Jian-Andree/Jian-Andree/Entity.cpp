//Entity.cpp

#include "stdafx.h"

#include "Entity.h"

Entity::Entity()
{

}

Entity::Entity(Vector2 entity_position, int entity_width, int entity_height)
{
}

void Entity::Init(std::string object_type, Alignment alignment, Type type)
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

void Entity::OnCollision(Type enemy_type)
{
}

Collider* Entity::getCollider()
{
	return collider;
}

Type Entity::getType()
{
	return type;
}

Alignment Entity::getAlignment()
{
	return alignment;
}

bool Entity::hasCollider()
{
	return collider != nullptr;
}