// LostSoulObject.cpp

#include "stdafx.h"
#include "LostSoulObject.h"

LostSoulObject::LostSoulObject()
{

}

LostSoulObject::LostSoulObject(Entity* enemydropping, Vector2 lostsoul_position, ConfigManager* config_mgr)
{
	current_animation = nullptr;

	position.x = enemydropping->getPosition().x + enemydropping->getWidth();
	position.y = enemydropping->getPosition().y + enemydropping->getHeight();
	width = config_mgr->ReadInt("lostsoulwidth");
	height = config_mgr->ReadInt("lostsoulheight");

	entity_offset_x = config_mgr->ReadInt("lostsouloffsetx");
	entity_offset_y = config_mgr->ReadInt("lostsouloffsety");

	flagged_for_death = false;

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

void LostSoulObject::Init(std::string object_type, Alignment lostsoul_alignment, Type lostsoul_type)
{
	alignment = lostsoul_alignment;
	type = lostsoul_type;

	current_animation->getSprite()->setPosition(position.x, position.y);
}

void LostSoulObject::Update(float deltatime)
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

void LostSoulObject::OnCollision(Entity* collision_entity, Type collision_type, Vector2 offset, Alignment other_alignment)
{
	if(other_alignment == PLAYER)
	{
		flagged_for_death = true;
	}	

}