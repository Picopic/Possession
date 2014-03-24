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

	used_counter = 0.0f;
	used_by_player = false;

	collider = new Collider;
	collider->position.x = position.x + entity_offset_x;
	collider->position.y = position.y + entity_offset_y;
	collider->extension = Vector2(width, height);

}

void AltarObject::Init(std::string object_type, Alignment altar_alignment, Type altar_type)
{
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

	if(used_by_player)
	{
		used_counter += deltatime;
		if(used_counter > 5.0)
		{
			used_by_player = false;
			used_counter = 0.0f;
		}
	}


	current_animation->getSprite()->setPosition(position.x, position.y);

}

void AltarObject::OnCollision(Entity* collision_entity, Type altar_type, Vector2 offset, Alignment altar_alignment)
{
	//if water-/wood-/firePoints <= 0, ta +1, h�nder i playerobject.cpp

	if(altar_alignment == PLAYER)
	{
		used_by_player = true;
	}
	
}