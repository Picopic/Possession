//Entity.h

#pragma once
#include "Collider.h"
#include <iostream>
#include "Enums.h"
#include "AnimatedSprite.h"

class Entity
{
public:
	Entity();
	Entity(Vector2 entity_position, int entity_width, int entity_height);
	virtual void Init(std::string object_type, Alignment alignment, Type type) = 0; //initiate the object
	virtual void Update(float deltatime) = 0; //apply logic to object
	void Cleanup();

	std::string getID();
	void setID(std::string new_ID);

	Alignment getAlignment();
	Collider* getCollider();
	Vector2 getPosition();
	void setPosition(Vector2 pos);
	bool hasCollider() const;
	Type getType();

	Vector2 getDirection();

	bool CreateProjectile();
	float getShootDelay();
	float getDelay();
	void setDelay(float new_delay);
	void resetShootDelay();

	bool IsFlaggedForDeath();

	int getWidth();
	int getHeight();

	void AddAnimation(AnimationName animation_name, AnimatedSprite* anim_sprite);
	AnimatedSprite* GetCurrentAnimation();

	virtual void OnCollision(Type collision_type, Vector2 offset, Alignment enemy_alignment);

	sf::RectangleShape shape;
protected:
	Collider *collider;
	Vector2 position;

	Alignment alignment;
	Type type;

	int width;
	int height;

	int hitpoints;

	std::string entity_ID;

	bool flagged_for_death;
	bool dead;

	//projectilehandling
	bool create_projectile;
	bool created_projectile;
	int max_projectile_count;
	float shooting_delay;
	float delay;
	Vector2 direction;

	//Animations
	AnimatedSprite* current_animation;
	std::map<AnimationName, AnimatedSprite*> animations;
	float time;
	void SetCurrentAnimation(AnimationName animation_name);
};