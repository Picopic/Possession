//Entity.cpp

#include "stdafx.h"



#include "Entity.h"

Entity::Entity()
{

}

void Entity::Init(std::string object_type, Alignment enemy_alignment, Type enemy_type)
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
	if(current_animation != nullptr)
	{
		delete current_animation;
		current_animation = nullptr;
	}
	if(player != nullptr)
	{
		player = nullptr;
	}
}

void Entity::OnCollision(Entity* collision_entity,Type collision_type, Vector2 offset, Alignment enemy_alignment)
{
}

Collider* Entity::getCollider()
{
	return collider;
}

sf::RectangleShape Entity::GetHitbox()
{
	return hitbox;
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

bool Entity::IsDead()
{
	return dead;
}

void Entity::FlagEntity()
{
	flagged_for_death = true;
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
		current_animation->SetCurrentFrame(0);
		current_animations_name = animation_name;
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

bool Entity::GetLostSoul()
{
	return drop_lostsoul;
}

//Enemy AI to avoid each other:
void Entity::SetPositions(Vector2 p_position)
{
	othersposition.push_back(p_position);
}

void Entity::ClearPositions()
{
	othersposition.clear();
}

void Entity::DontStack()
{
	for (int i=0; i<othersposition.size(); i++){
		float deltaY = position.y - othersposition.at(i).y;
		float deltaX = position.x - othersposition.at(i).x;
		float distance = sqrt(deltaY*deltaY+deltaX*deltaX);

		if(distance == 0)
			distance = 0.001;

		if (distance < 70){
			float offset = 70 - distance;
			float offsetY = deltaY*offset/distance;
			float offsetX = deltaX*offset/distance;	

			position.x += offsetX;
			position.y += offsetY;

		}
	}
}

void Entity::setplayer(Entity* p_player){
	player = p_player;
}