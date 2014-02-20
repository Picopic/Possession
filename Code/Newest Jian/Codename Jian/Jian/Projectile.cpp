//Projectile.cpp

#include "stdafx.h"

#include "Projectile.h"

Projectile::Projectile()
{

}

Projectile::Projectile(Entity* shooter_entity, int projectile_width, int projectile_height, Vector2 projectile_direction)
{
	current_animation = nullptr;

	width = projectile_width;
	height = projectile_height;

	if(projectile_direction.x == 1)
	{
		position.x = shooter_entity->getPosition().x + shooter_entity->getWidth();
		position.y = shooter_entity->getPosition().y + (shooter_entity->getHeight()/2);
	}
	else if(projectile_direction.x == -1)
	{
		position.x = shooter_entity->getPosition().x;
		position.y = shooter_entity->getPosition().y + (shooter_entity->getHeight()/2);
	}

	start_pos = position;
	direction = projectile_direction;

	dead = false;
	death_animation_time = 0.0f;
	flagged_for_death = false;
	create_projectile = false;

	collider = new Collider;
	collider->position = position;
	collider->extension = Vector2(width, height);
}

void Projectile::Init(std::string object_type, Alignment projectile_alignment, Type projectile_type)
{
	entity_ID = object_type;
	alignment = projectile_alignment;
	type = projectile_type;

	current_animation->getSprite()->setPosition(position.x, position.y);
	
	//which animation?
	if(direction.x == 1)
	{
	}
	else
	{
	}
}

void Projectile::Update(float deltatime)
{
	current_animation->Update(deltatime);
	if(hasCollider())
	{
		position.x += deltatime * 300 * direction.x;
		collider->position = position;
	}
	
	current_animation->getSprite()->setPosition(position.x, position.y);

	//out of screen actions
	if((position.x + width) < (start_pos.x-680))
	{
		flagged_for_death = true;
	}
	else if(position.x > (start_pos.x+680))
	{
		flagged_for_death = true;
	}
	else if((position.y + height) < 0)
	{
		flagged_for_death = true;
	}
	else if(position.y > 720)
	{
		flagged_for_death = true;
	}
	if(dead)
	{
		if(collider != nullptr)
		{
			delete collider;
			collider = nullptr;
		}
		death_animation_time += deltatime;
		if(death_animation_time > 0.5)
		{
			flagged_for_death = true;
		}
	}
}

void Projectile::OnCollision(Type collision_type, Vector2 offset, Alignment enemy_alignment)
{
	dead = true;
	if(direction.x == 1)
	{
		SetCurrentAnimation(DEATHRIGHT);
	}
	else
	{
		SetCurrentAnimation(DEATHLEFT);
	}
}