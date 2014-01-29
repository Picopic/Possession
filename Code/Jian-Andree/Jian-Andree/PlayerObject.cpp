//PlayerObject.cpp

#include "stdafx.h"

#include "PlayerObject.h"

PlayerObject::PlayerObject()
{

}

PlayerObject::~PlayerObject()
{

}

//Get the objects position
const Vector2 &PlayerObject::GetPosition() const
{
	return position;
}
//set the objects position
void PlayerObject::SetPosition(const Vector2 &_position)
{
	position = _position;
}

//Does the object contain a sprite?
bool PlayerObject::HasSprite() const
{
	return sprite != nullptr;
}
//Retrieve the sprite being used
sf::Sprite* PlayerObject::GetSprite()
{
	return sprite;
}

//Does the object have a collider
bool PlayerObject::HasCollider() const
{
	return collider != nullptr;
}
//Retrieve the objects collider
Collider* PlayerObject::GetCollider()
{
	return collider;
}