// Vector2.cpp

#include "stdafx.h"

#include <cmath>
#include "Vector2.h"

Vector2::Vector2() {
	x = 0.0f;
	y = 0.0f;
};

Vector2::Vector2(const Vector2 &rhs) {
	x = rhs.x;
	y = rhs.y;
};

Vector2::Vector2(float _x, float _y) {
	x = _x;
	y = _y;
};

Vector2 &Vector2::operator=(const Vector2 &rhs) {
	this->x = rhs.x;
	this->y = rhs.y;
	return *this;
};

Vector2 &Vector2::operator+=(const Vector2 &rhs) {
	x += rhs.x;
	y += rhs.y;
	return *this;
};

Vector2 &Vector2::operator-=(const Vector2 &rhs) {
	x -= rhs.x;
	y -= rhs.y;
	return *this;
};

Vector2 &Vector2::operator*=(float value) {
	x *= value;
	y *= value;
	return *this;
};

Vector2 &Vector2::operator/=(float value) {
	x /= value;
	y /= value;
	return *this;
};

Vector2 Vector2::operator+(const Vector2 &rhs) {
	return Vector2(x + rhs.x, y + rhs.y);
};

Vector2 Vector2::operator-(const Vector2 &rhs) {
	return Vector2(x - rhs.x, y - rhs.y);
};

Vector2 Vector2::operator*(float value) {
	return Vector2(x * value, y * value);
};

Vector2 Vector2::operator/(float value) {
	return Vector2(x / value, y / value);
};

bool Vector2::operator==(const Vector2 &rhs) {
	const float epsilon = 0.00001f;
	return fabs(x - rhs.x) < epsilon && fabs(y - rhs.y) < epsilon;
};

bool Vector2::operator!=(const Vector2 &rhs) {
	return !(*this == rhs);
};

float Vector2::Length() {
	return sqrtf(x * x + y * y);
};

void Vector2::Normalise() {
	float length = Length();
	if(length > 0.0f) {
		x /= length;
		y /= length;
	};
};
