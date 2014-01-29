//Entity.h
#include "Collider.h"

class Entity
{
public:
	Entity();
	void Init();
	void Update();

private:
	Collider *collider;
	Vector2 position;
};