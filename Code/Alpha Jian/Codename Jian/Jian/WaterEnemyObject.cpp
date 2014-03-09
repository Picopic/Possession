//WaterEnemyObject.cpp

#include "stdafx.h"

#include "WaterEnemyObject.h"

WaterEnemyObject::WaterEnemyObject()
{

}

WaterEnemyObject::WaterEnemyObject(Vector2 enemy_position, int enemy_width, int enemy_height)
{
	current_animation = nullptr;

	position = enemy_position;
	width = enemy_width;
	height = enemy_height;

	flagged_for_death = false;
	hitpoints = 10;
	
	collider = new Collider;
	collider->position = position;
	collider->extension = Vector2(width, height);
}

void WaterEnemyObject::Init(std::string object_type, Alignment enemy_alignment, Type enemy_type)
{
	alignment = enemy_alignment;
	type = enemy_type;
}

void WaterEnemyObject::Update(float deltatime)
{
	if(hasCollider())
	{
		collider->position = position;
		//shape.setPosition(position.x, position.y);
	}

	if(hitpoints <= 0)
	{
		flagged_for_death = true;
	}
}

void WaterEnemyObject::OnCollision(Entity* collision_entity, Type enemy_type, Vector2 offset, Alignment enemy_alignment)
{
	if(enemy_alignment == FRIENDBULLET)
	{
		if(enemy_type == WOOD)
			{
				hitpoints -= 3;
			}
			else if(enemy_type == WATER)
			{
				hitpoints -= 2;
			}
			else if(enemy_type == FIRE)
			{
				hitpoints--;
			}
	}
	else if(enemy_alignment == PLAYER)
	{

	}
	
}
