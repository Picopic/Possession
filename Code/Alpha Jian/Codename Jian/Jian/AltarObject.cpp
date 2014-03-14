// AltarObject.cpp

#include "stdafx.h"
#include "AltarObject.h"

AltarObject::AltarObject()
{

}

AltarObject::AltarObject(Vector2 altar_position, ConfigManager* config_mgr)
{  
	current_animation = nullptr;
	flagged_for_death = false;

	position = altar_position;
	width = config_mgr->ReadInt("altarwidth");
	height = config_mgr->ReadInt("altarheight");

	entity_offset_x = config_mgr->ReadInt("altaroffsetx");
	entity_offset_y = config_mgr->ReadInt("altaroffsety");

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
		current_animation->getSprite()->setPosition(collider->position.x, collider->position.y);
		collider->position.x = position.x + entity_offset_x;
		collider->position.y = position.y + entity_offset_y;
		hitbox.setPosition(collider->position.x, collider->position.y);
	}

	current_animation->getSprite()->setPosition(position.x, position.y);
}

void AltarObject::OnCollision(Entity* collision_entity, Type altar_type, Vector2 offset, Alignment altar_alignment)
{
	//if water-/wood-/firePoints <= 0, ta +1, händer i playerobject.cpp
	
}