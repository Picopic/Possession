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

	if(projectile_direction == Vector2(1, 0))
	{
		position.x = shooter_entity->getPosition().x + shooter_entity->getWidth();
		position.y = shooter_entity->getPosition().y + (shooter_entity->getHeight()/2 - height/2);
	}
	else if(projectile_direction == Vector2(-1, 0))
	{
		position.x = shooter_entity->getPosition().x;
		position.y = shooter_entity->getPosition().y + (shooter_entity->getHeight()/2 - height/2);
	}
	/*
	else if(projectile_direction == Vector2(0, 1))
	{
		position.y = shooter_entity->getPosition().y + shooter_entity->getHeight();
		position.x = shooter_entity->getPosition().x + (shooter_entity->getWidth()/2 - width/2);
	}
	else if(projectile_direction == Vector2(0, -1))
	{
		position.y = shooter_entity->getPosition().y;
		position.x = shooter_entity->getPosition().x + (shooter_entity->getWidth()/2 - width/2);
	}
	*/

	direction = projectile_direction;

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

	start_pos = position;

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
	position.x += deltatime * 300 * direction.x;

	
	if(hasCollider())
	{
		collider->position = position;
		current_animation->getSprite()->setPosition(collider->position.x, collider->position.y);
	}

	//out of screen actions
	if((position.x + width) < (start_pos.x - 640))
	{
		flagged_for_death = true;
	}
	else if(position.x > (start_pos.x + 640))
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
}

void Projectile::OnCollision(Type collision_type, Vector2 offset, Alignment enemy_alignment)
{
	flagged_for_death = true;
}