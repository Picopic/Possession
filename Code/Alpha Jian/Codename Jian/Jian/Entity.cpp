//Entity.cpp

#include "stdafx.h"



#include "Entity.h"

Entity::Entity()
{

}

Entity::Entity(Vector2 entity_position, int entity_width, int entity_height)
{
}

void Entity::Init(std::string object_type, Alignment alignment, Type type)
{

}

void Entity::Update(float deltatime)
{
}

void Entity::Cleanup()
{
	if(hasCollider())
	{
		delete collider;
		collider = nullptr;
	}
}

std::string Entity::getID()
{
	return entity_ID;
}

void Entity::setID(std::string new_ID)
{
	entity_ID = new_ID;
}

void Entity::OnCollision(Type collision_type, Vector2 offset, Alignment enemy_alignment)
{
}

Collider* Entity::getCollider()
{
	return collider;
}

Type Entity::getType()
{
	return type;
}

Alignment Entity::getAlignment()
{
	return alignment;
}

bool Entity::hasCollider() const
{
	return collider != nullptr;
}

bool Entity::IsFlaggedForDeath()
{
	return flagged_for_death;
}

Vector2 Entity::getDirection()
{
	return direction;
}

bool Entity::CreateProjectile()
{
	return create_projectile;
}

void Entity::resetShootDelay() {
	shooting_delay=0.0f;
}

Vector2 Entity::getPosition()
{
	return position;
}

void Entity::setPosition(Vector2 pos) {
	position = pos;
}

float Entity::getShootDelay()
{
	return shooting_delay;
}

float Entity::getDelay()
{
	return delay;
}

void Entity::setDelay(float new_delay)
{
	delay = new_delay;
}

int Entity::getWidth()
{
	return width;
}

int Entity::getHeight()
{
	return height;
}

void Entity::AddAnimation(AnimationName animation_name, AnimatedSprite* anim_sprite)
{
	animations.insert(std::pair<AnimationName, AnimatedSprite*>(animation_name, anim_sprite));
	if(current_animation == nullptr)
	{
		auto it = animations.find(animation_name);
		current_animation = it->second;
	}
}

AnimatedSprite* Entity::GetCurrentAnimation()
{
	return current_animation;
}

void Entity::SetCurrentAnimation(AnimationName animation_name)
{
	auto it = animations.find(animation_name);
	if(it == animations.end())
	{

	}
	else
	{
		current_animation = it->second;
	}
}

bool Entity::CanCollide()
{
	return can_collide;
}

sf::Sprite* Entity::GetSprite()
{
	return current_animation->getSprite();
}

/*void Entity::GetLostSoul()
{
	return drop_lostsoul;
}*/
