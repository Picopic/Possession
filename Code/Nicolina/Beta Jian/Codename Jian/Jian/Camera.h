#pragma once
#include "stdafx.h"
#include "Vector2.h"

class Camera
{
private:
	sf::Vector2f position;

public:
	Camera(void);
	~Camera(void);

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);

	void moveX(float x);
};

