// Collider.h

#pragma once

#include "Vector2.h"

class Collider {
public:
	Collider();
	Collider(const Vector2 &position, const Vector2 &extension);

	bool Overlap(Collider &other, Vector2 &offset);

	Vector2 position;
	Vector2 extension;
};
