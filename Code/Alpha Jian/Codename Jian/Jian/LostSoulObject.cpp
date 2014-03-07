// LostSoulObject.cpp

#include "stdafx.h"
#include "LostSoulObject.h"

LostSoulObject::LostSoulObject()
{

}

LostSoulObject::LostSoulObject(Entity* enemydropping, int lostsoul_width, int lostsoul_height, Vector2 lostsoul_position)
{
	current_animation = nullptr;

	position = lostsoul_position;
	width = lostsoul_width;
	height = lostsoul_height;

	flagged_for_death = false;

	collider = new Collider;
	collider->position = position;
	collider->extension = Vector2(width, height);

}

void LostSoulObject::Init(std::string object_type, Alignment lostsoul_alignment, Type lostsoul_type)
{
	entity_ID = object_type;

	alignment = lostsoul_alignment;
	type = lostsoul_type;

	current_animation->getSprite()->setPosition(position.x, position.y);
}

void LostSoulObject::Update(float deltatime)
{
	
	current_animation->Update(deltatime);
	if(hasCollider())
	{
		collider->position = position;
		current_animation->getSprite()->setPosition(collider->position.x, collider->position.y);
	}

	current_animation->getSprite()->setPosition(position.x, position.y);

}

void LostSoulObject::OnCollision(Type collision_type, Vector2 offset, Alignment other_alignment)
{
	if(other_alignment == PLAYER)
	{
		flagged_for_death = true;
	}	

}