// AltarObject.cpp

#include "stdafx.h"
#include "AltarObject.h"

AltarObject::AltarObject()
{

}

AltarObject::AltarObject(Vector2 altar_position, ConfigManager* config_mgrt)
{
	current_animation = nullptr;

	position = altar_position;
	width = config_mgrt->ReadInt("altarwidth");
	height = config_mgrt->ReadInt("altarheight");

	entity_offset_x = config_mgrt->ReadInt("altaroffsetx");
	entity_offset_y = config_mgrt->ReadInt("altaroffsety");

	used_counter = 0.0f;
	used_by_player = false;

	collider = new Collider;
	collider->position.x = position.x + entity_offset_x;
	collider->position.y = position.y + entity_offset_y;
	collider->extension = Vector2(width, height);

	hitbox.setSize(sf::Vector2f(width, height));
	hitbox.setOrigin(0, 0);
	hitbox.setPosition(collider->position.x, collider->position.y);
	hitbox.setFillColor(sf::Color(0,0,0,0));
	hitbox.setOutlineThickness(1);
	hitbox.setOutlineColor(sf::Color(255,0,0,255));
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
	//if water-/wood-/firePoints <= 0, ta +1, händer i playerobject.cpp

	if(altar_alignment == PLAYER)
	{
		used_by_player = true;
	}
	
}