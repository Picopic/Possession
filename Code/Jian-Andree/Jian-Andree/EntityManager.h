//EntityManager.h

#pragma once
#include "Collider.h"
class PlayerObject;

enum Alignment
{
	FRIEND,
	FOE,
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
	PlayerObject *player;
};