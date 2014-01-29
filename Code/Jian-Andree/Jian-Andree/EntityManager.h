//EntityManager.h

#pragma once
#include "Collider.h"

enum Alignment
{
	FRIEND,
	FOE,
	FRIENDBULLET,
	FOEBULLET,
	ALIGNMENT_SIZE
};

enum Type
{
	FIRE,
	WATER,
	WOOD,
	TYPE_SIZE
};

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

private:
	
};