//FireEnemyObject

#include "stdafx.h"

#include "FireEnemyObject.h"

FireEnemyObject::FireEnemyObject()
{

}

FireEnemyObject::FireEnemyObject(Vector2 enemy_position, int enemy_width, int enemy_height)
{
	current_animation = nullptr;

	position = enemy_position;
	width = enemy_width;
	height = enemy_height;

	flagged_for_death = false;
	dead = false;

	hitpoints = 5;

	time = 0.0f;

	collider = new Collider;
	collider->position = position;
	collider->extension = Vector2(width, height);

}

void FireEnemyObject::Init(std::string object_type, Alignment enemy_alignment, Type enemy_type)
{
	entity_ID = object_type;

	alignment = enemy_alignment;
	type = enemy_type;

	current_animation->getSprite()->setPosition(position.x, position.y);
}

void FireEnemyObject::Update(float deltatime)
{
	current_animation->Update(deltatime);
	if(hasCollider())
	{
		position = collider->position;
		shape.setPosition(position.x, position.y);
	}
	if(hitpoints <= 0 && !dead)
	{
		dead = true;
		SetCurrentAnimation(DEATH);
		current_animation->getSprite()->setPosition(position.x, position.y);
		Cleanup();
		time += deltatime;
	}
	if(dead)
	{
		time += deltatime;
	}
	if(time > current_animation->GetNumberOfFrames() * current_animation->GetFrameDuration())
	{
		flagged_for_death = true;
	}
}

void FireEnemyObject::OnCollision(Type enemy_type, Vector2 offset, Alignment enemy_alignment)
{
	if(enemy_alignment == FRIENDBULLET)
	{
		if(enemy_type == WATER)
		{
			hitpoints -= 3;
		}
		else if(enemy_type == FIRE)
		{
			hitpoints -= 2;
		}
		else if(enemy_type == WOOD)
		{
			hitpoints--;
		}
	}
	
}