//Projectile.h

#include "Entity.h"

class Projectile : public Entity
{
public:
	Projectile();
	Projectile(Vector2 projectile_position, int projectile_width, int projectile_height, Vector2 projectile_direction);

	void Init(std::string object_type, Alignment alignment, Type type);
	void Update(float deltatime);

	void OnCollision(Type collision_type, Vector2 offset);

private:
};