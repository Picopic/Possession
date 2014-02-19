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

	//shooting
	delay = 0.0f;
	shooting_delay = 0.001f;
	create_projectile = false;
	created_projectile = false;

	//collision
	entity_offset_x = 50;
	entity_offset_y = 40;

	//movement
	velocity = 50;
	direction = Vector2(-1, 1);

	movement_time = 0.0f;
	death_animation_time = 0.0f;

	collider = new Collider;
	collider->position.x = position.x + entity_offset_x;
	collider->position.y = position.y + entity_offset_y;
	collider->extension = Vector2(width, height);

}

void FireEnemyObject::Init(std::string object_type, Alignment enemy_alignment, Type enemy_type)
{
	entity_ID = object_type;

	alignment = enemy_alignment;
	type = enemy_type;

	current_animation->getSprite()->setPosition(position.x, position.y);
}

void FireEnemyObject::Update(float deltatime, Entity* player)
{
	//Firstly update the animation
	current_animation->Update(deltatime);
	//movement
	if(current_animations_name != ATTACKLEFT || current_animations_name != ATTACKRIGHT)
	{
		//
		
		//
	}
	

	//Attack
	
	if(created_projectile)
	{
		shooting_delay += deltatime;
	}

	if(shooting_delay == 0.001f && !created_projectile)
	{
		create_projectile = true;
		created_projectile = true;
		SetCurrentAnimation(ATTACKLEFT);
	}
	else
	{
		create_projectile = false;
	}

	if(shooting_delay > delay)
	{
		shooting_delay = 0.001f;
		created_projectile = false;
	}
	

	//Death
	if(hitpoints <= 0 && !dead)
	{
		dead = true;
		SetCurrentAnimation(DEATHLEFT);
		current_animations_name = DEATHLEFT;
		current_animation->getSprite()->setPosition(position.x, position.y);
		Cleanup();
		death_animation_time += deltatime;
	}
	if(dead)
	{
		death_animation_time += deltatime;
		if(death_animation_time > current_animation->GetNumberOfFrames() * current_animation->GetFrameDuration())
		{
			flagged_for_death = true;
		}
	}
	

	//Lastly update the sprites position if there is a collider
	if(hasCollider())
	{
		collider->position.x = position.x + entity_offset_x;
		collider->position.y = position.y + entity_offset_y;
		current_animation->getSprite()->setPosition(position.x, position.y);
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

bool FireEnemyObject::AttackRaycast(Entity* player)
{
	if(player->getPosition().y > (position.y + 30) > (player->getPosition().y + player->getHeight()))
	{
		if((player->getPosition().x - position.x) < 0 && direction.x == 1)
		{
			return true;
		}
		else if((player->getPosition().x - position.x) > 0 && direction.x == -1)
		{
			return true;
		}
		
	}
	else
	{
		return false;
	}
}