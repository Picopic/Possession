// AltarObject.cpp

#include "stdafx.h"
#include "AltarObject.h"

AltarObject::AltarObject()
{

}

AltarObject::AltarObject(Vector2 altar_position, int altar_width, int altar_height)
{
	current_animation = nullptr;

	position = altar_position;
	width = altar_width;
	height = altar_height;

	entity_offset_x = -50; //change according to the sprites
	entity_offset_y = -30; //^

	collider = new Collider;
	collider->position.x = position.x + entity_offset_x;
	collider->position.y = position.y + entity_offset_y;
	collider->extension = Vector2(width, height);

}

void AltarObject::Init(std::string object_type, Alignment altar_alignment, Type altar_type)
{
	entity_ID = object_type;

	alignment = altar_alignment;
	type = altar_type;

	current_animation->getSprite()->setPosition(position.x, position.y);
}

void AltarObject::Update(float deltatime)
{
	current_animation->Update(deltatime);
	if(hasCollider())
	{
		collider->position = position;
		current_animation->getSprite()->setPosition(collider->position.x, collider->position.y);
	}

	current_animation->getSprite()->setPosition(position.x, position.y);

}

void AltarObject::OnCollision(Type altar_type, Vector2 offset, Alignment altar_alignment)
{
	//if water-/wood-/firePoints <= 0, ta +1, händer i playerobject.cpp
	
}