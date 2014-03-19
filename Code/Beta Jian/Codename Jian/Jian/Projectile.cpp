//Projectile.cpp

#include "stdafx.h"

#include "Projectile.h"

Projectile::Projectile()
{

}

Projectile::Projectile(Entity* shooter_entity, ConfigManager* config_manager, Vector2 projectile_direction)
{
	current_animation = nullptr;

	Hit = false;

	switch (shooter_entity->getType())
	{
	case FIRE:
		entity_offset_x = config_manager->ReadInt("fireprojectileoffsetx");
		entity_offset_y = config_manager->ReadInt("fireprojectileoffsety");
		width = config_manager->ReadInt("fireprojectilewidth");
		height = config_manager->ReadInt("fireprojectileheight");
		break;
	case WATER:
		entity_offset_x = config_manager->ReadInt("waterprojectileoffsetx");
		entity_offset_y = config_manager->ReadInt("waterprojectileoffsety");
		width = config_manager->ReadInt("waterprojectilewidth");
		height = config_manager->ReadInt("waterprojectileheight");
		break;
	case WOOD:
		entity_offset_x = config_manager->ReadInt("woodprojectileoffsetx");
		entity_offset_y = config_manager->ReadInt("woodprojectileoffsety");
		width = config_manager->ReadInt("woodprojectilewidth");
		height = config_manager->ReadInt("woodprojectileheight");
		break;
	}

	if(projectile_direction.x == 1)
	{
		position.x = shooter_entity->getPosition().x + shooter_entity->GetSprite()->getTextureRect().width/2;
		position.y = (shooter_entity->getCollider()->position.y + shooter_entity->getCollider()->extension.y) - 250;
	}
	else if(projectile_direction.x == -1)
	{
		position.x = shooter_entity->getPosition().x;
		position.y = (shooter_entity->getCollider()->position.y + shooter_entity->getCollider()->extension.y) - 250;
	}

	start_pos = position;
	direction = projectile_direction;

	speed = 300;

	dead = false;
	death_animation_time = 0.0f;
	flagged_for_death = false;
	create_projectile = false;

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

	player = nullptr;
}

void Projectile::Init(std::string object_type, Alignment projectile_alignment, Type projectile_type)
{
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
	if(!Hit)
	{
		position.x += deltatime * speed * direction.x;
	}
	if(hasCollider())
	{
		//position.x += deltatime * speed * direction.x;
		collider->position.x = position.x + entity_offset_x;
		collider->position.y = position.y + entity_offset_y;
		hitbox.setPosition(collider->position.x, collider->position.y);
	}
	
	current_animation->getSprite()->setPosition(position.x, position.y);

	//out of screen actions
	if((position.x + width) < (start_pos.x-680))
	{
		OutOfBounds();
	}
	else if(position.x > (start_pos.x+680))
	{
		OutOfBounds();
	}
	else if((position.y + height) < 0)
	{
		OutOfBounds();
	}
	else if(position.y > 1080)
	{
		OutOfBounds();
	}

	if(dead)
	{
		death_animation_time += deltatime;
		if(death_animation_time > current_animation->GetNumberOfFrames() * current_animation->GetFrameDuration())
		{
			flagged_for_death = true;
		}
	}
}

void Projectile::OnCollision(Entity* collision_entity, Type collision_type, Vector2 offset, Alignment enemy_alignment)
{
	Hit = true;
	dead = true;

	if(collider != nullptr)
	{
		delete collider;
		collider = nullptr;
	}

	if(direction.x == 1)
	{
		SetCurrentAnimation(DEATHRIGHT);
	}
	else
	{
		SetCurrentAnimation(DEATHLEFT);
	}
}

void Projectile::OutOfBounds()
{
	if(!dead)
	{
		dead = true;

		if(collider != nullptr)
		{
			delete collider;
			collider = nullptr;
		}
		if(direction.x == 1)
		{
			SetCurrentAnimation(FADEOUTRIGHT);
		}
		else
		{
			SetCurrentAnimation(FADEOUTLEFT);
		}
	}
	else
	{

	}
}