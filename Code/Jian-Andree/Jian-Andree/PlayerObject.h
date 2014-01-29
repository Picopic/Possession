//PlayerObject.h

#pragma once
#include "Collider.h"
#include "EntityManager.h"

class PlayerObject : public EntityManager
{
public:
	PlayerObject();
	~PlayerObject();
	PlayerObject(sf::Sprite sprite, Collider collider, Vector2 position, int width, int height, Type _type, Alignment _alignment);

	const Vector2 &GetPosition() const;
	void SetPosition(const Vector2 &position);

	bool HasSprite() const;
	sf::Sprite* GetSprite();

	bool HasCollider() const;
	Collider* GetCollider();

private:
	Type current_type;
	Alignment alignment;

	sf::Sprite *sprite;
	Collider *collider;
	Vector2 position;
};