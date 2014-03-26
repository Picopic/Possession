// Collider.cpp

#include "stdafx.h"

#include <cstdio>
#include <cmath>
#include "Collider.h"

Collider::Collider() 
: position(0.0f, 0.0f)
, extension(0.0f, 0.0f)
{
};

Collider::Collider(const Vector2 &_position, const Vector2 &_extension)
: position(_position)
, extension(_extension)
{
};

bool Collider::Overlap(Collider &other, Vector2 &offset) 
{

	float A = extension.x * 0.5f;
	float B = other.extension.x * 0.5f;
	float C = (position.x + A) - (other.position.x + B);


	if(fabs(C) <= A + B) {

		float Q = extension.y * 0.5f;
		float P = other.extension.y * 0.5f;
		float Z = (position.y + Q) - (other.position.y + P);


		//wut.png
		if(fabs(Z) <= Q + P) {
			float dx = ceilf(fabs(C) - (A + B));
			float dy = ceilf(fabs(Z) - (Q + P));
			if(dx >= dy) {
				if(position.x < other.position.x) {
					dx = -dx;
				};
				offset.x = dx;
				other.position.x += dx;
			}
			else {
				if(position.y < other.position.y) {
					dy = -dy;
				};
				offset.y = dy;
				other.position.y += dy;
			};
			
			return true;
		};
	};
	return false;
};
