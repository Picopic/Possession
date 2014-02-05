//Entity.h

#pragma once
#include "Collider.h"
#include <iostream>

enum Alignment
{
	PLAYER,
	WATERFOE,
	WOODFOE,
	FIREFOE,
	FRIENDBULLET,
	WATERFOEBULLET,
	WOODFOEBULLET,
	FIREFOEBULLET,
	ALIGNMENT_SIZE
};

enum Type
{
	FIRE,
	WATER,
	WOOD,
	TYPE_SIZE
};

class Entity
{
public:
	Entity();
	Entity(Vector2 entity_position, int entity_width, int entity_height);
	virtual void Init(std::string object_type, Alignment alignment, Type type) = 0; //initiate the object
	virtual void Update(float deltatime) = 0; //move and/or animate the object

	std::string getID();
	void setID(std::string new_ID);

	Alignment getAlignment();
	Collider* getCollider();
	Vector2 getPosition();
	bool hasCollider() const;
	Type getType();

	Vector2 getDirection();

	bool CreateProjectile();
	float getShootDelay();
	float getDelay();
	void setDelay(float new_delay);

	bool IsFlaggedForDeath();

	int getWidth();
	int getHeight();


	virtual void OnCollision(Type collision_type, Vector2 offset);

	sf::RectangleShape shape;
protected:
	Collider *collider;
	Vector2 position;

	Alignment alignment;
	Type type;

	int width;
	int height;

	std::string entity_ID;

	bool flagged_for_death;

	//projectilehandling
	bool create_projectile;
	bool created_projectile;
	int max_projectile_count;
	float shooting_delay;
	float delay;

	Vector2 direction;
};