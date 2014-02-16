//Projectile.h

#include "Entity.h"

class Projectile : public Entity
{
public:
	Projectile();
	Projectile(Entity* shooter_entity, int projectile_width, int projectile_height, Vector2 projectile_direction);

	void Init(std::string object_type, Alignment alignment, Type type);
	void Update(float deltatime);

	void OnCollision(Type collision_type, Vector2 offset, Alignment enemy_alignment);

private:
};