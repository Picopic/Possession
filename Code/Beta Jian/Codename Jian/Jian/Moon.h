//Moon.h

#pragma once
#include "stdafx.h"

class Moon

{
private:
	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite sprite;

public:
	Moon(void);
	~Moon(void);
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);

	void draw(sf::RenderWindow* window);
	
	bool initialize();

	void moveX(float x);
};

