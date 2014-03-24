//Projectile.cpp

#include "stdafx.h"

#include "Projectile.h"

Projectile::Projectile()
{

}

Projectile::Projectile(Entity* shooter_entity, Type ProjectileType, ConfigManager* config_manager, Vector2 projectile_direction, bool DoubleShot, Vector2 ProjectilePosition)
{
	Doubleshot = DoubleShot;

	current_animation = nullptr;

	type = ProjectileType;

	m_ShooterEntity = shooter_entity;

	Hit = false;

	switch (type)
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

	position = ProjectilePosition;

	start_pos = position;
	direction.x = projectile_direction.x;
	direction.y = projectile_direction.y;

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
	//Water enemy attack
	if(m_ShooterEntity->getAlignment() == WATERFOE)
	{
		float dX, dY, Hypotenusa;
		//Home in on player
		dX = (player->getPosition().x + player->GetOffsetX() + player->getWidth()/2) - 
			(m_ShooterEntity->getPosition().x + m_ShooterEntity->GetOffsetX() + m_ShooterEntity->getWidth()/2);
		dY = (player->getPosition().y + player->GetOffsetY() + player->getHeight()/2) -
			(m_ShooterEntity->getPosition().y + m_ShooterEntity->GetOffsetY() + m_ShooterEntity->getHeight()/2);

		Hypotenusa = sqrtf(dX * dX + dY * dY);

		direction = Vector2(dX/Hypotenusa, dY/Hypotenusa);
	}
	//end of water enemy attack
}

void Projectile::Update(float deltatime)
{
	current_animation->Update(deltatime);

	if(!Hit)
	{
		position.x += deltatime * speed * direction.x;
		position.y += deltatime * speed * direction.y;
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
	else if((position.y + height) < (start_pos.y - 340))
	{
		OutOfBounds();
	}
	else if(position.y > (start_pos.y + 700))
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