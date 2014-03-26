//Wall.cpp

#include "stdafx.h"

#include "Wall.h"

Wall::Wall()
{

}

//Constructor with some initialising parameters
Wall::Wall(Vector2 entity_position, int entity_width, int entity_height)
{
	current_animation = nullptr;

	position = entity_position;
	width = entity_width;
	height = entity_height;

	//Existence variables
	hitpoints = 10;
	dead = false;
	flagged_for_death = false;

	//Time
	death_animation_time = 0.0f;
	movement_time = 0.0f;

	//Collision
	entity_offset_x = 0;
	entity_offset_y = 0;
	can_collide = true;

	collider = new Collider;
	collider->position.x = position.x + entity_offset_x;
	collider->position.y = position.y + entity_offset_y;
	collider->extension = Vector2(width, height);
}

//Inherited Initialising function
void Wall::Init(std::string object_type, Alignment entity_alignment, Type entity_type)
{
	//Identity variables
	alignment = entity_alignment;
	type = entity_type;
}

//Inherited Update function
void Wall::Update(float deltatime)
{
	current_animation->Update(deltatime);

	//Is dead?
	if(hitpoints <= 0)
	{
		if(hasCollider())
		{
			delete collider;
			collider = nullptr;
		}
		dead = true;
		flagged_for_death = true;
		//SetCurrentAnimation(DEATHLEFT);
		//current_animations_name = DEATHLEFT;
	}
	current_animation->getSprite()->setPosition(position.x, position.y);
}

void Wall::OnCollision(Type collision_type, Vector2 offset, Alignment enemy_alignment)
{
	if(enemy_alignment == FRIENDBULLET)
	{
		switch (collision_type)
		{
		case FIRE:
			if(type == WOOD)
			{
				hitpoints--;
			}
			break;
		case WATER:
			if(type == FIRE)
			{
				hitpoints--;
			}
			break;
		case WOOD:
			if(type == WATER)
			{
				hitpoints--;
			}
			break;
		}
	}
}