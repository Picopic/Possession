//Projectile.h

#include "Entity.h"

class Projectile : public Entity
{
public:
	Projectile();
	Projectile(Entity* shooter_entity, Type Projectiletype, ConfigManager* config_manager, Vector2 projectile_direction, bool DoubleShot, Vector2 ProjectilePosition);

	void Init(std::string object_type, Alignment alignment, Type type);
	void Update(float deltatime);

	void OnCollision(Entity* collision_entity, Type collision_type, Vector2 offset, Alignment enemy_alignment);

	void OutOfBounds();

private:
	bool Hit;
	//Power up
	float DoubleshotTimer;

	Entity* m_ShooterEntity;
};