//SMFogB.h

#pragma once
#include "stdafx.h"

class SMFogB

{
private:
	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite sprite;

public:
	SMFogB(void);
	~SMFogB(void);
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);

	void draw(sf::RenderWindow* window);
	
	bool initialize();

	void moveX(float x);
};
