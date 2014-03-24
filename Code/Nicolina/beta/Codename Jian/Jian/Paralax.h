#pragma once
#include "stdafx.h"

class Paralax

{
private:
	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite sprite;

public:
	Paralax(void);
	~Paralax(void);
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);

	void draw(sf::RenderWindow* window);
	
	bool initialize();

	void moveX(float x);
};

