//Projectile.cpp

#include "stdafx.h"

#include "Projectile.h"

Projectile::Projectile()
{

}

Projectile::Projectile(Entity* shooter_entity, int projectile_width, int projectile_height, Vector2 projectile_direction)
{
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

	shape.setSize(sf::Vector2f(width, height));
	shape.setPosition(position.x, position.y);
	
	shape.setFillColor(sf::Color(0xE5, 0x68, 0x2B));
	//std::cout << "projectile x: " << direction.x << "\tprojectile y: " << direction.y << std::endl;
}

void Projectile::Update(float deltatime)
{
	shape.move(deltatime * 300 * direction.x, deltatime * 300 * direction.y);
	collider->position.x = shape.getPosition().x;
	collider->position.y = shape.getPosition().y;
	
	//out of screen actions
	if((shape.getPosition().x + width) < 0)
	{
		flagged_for_death = true;
	}
	else if(shape.getPosition().x > 1280)
	{
		flagged_for_death = true;
	}
	else if((shape.getPosition().y + height) < 0)
	{
		flagged_for_death = true;
	}
	else if(shape.getPosition().y > 720)
	{
		flagged_for_death = true;
	}
}

void Projectile::OnCollision(Type collision_type, Vector2 offset)
{
	flagged_for_death = true;
}