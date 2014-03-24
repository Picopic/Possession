//Paralax2.h


#pragma once
#include "stdafx.h"

class Paralax2

{
private:
	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite sprite;

public:
	Paralax2(void);
	~Paralax2(void);
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);

	void draw(sf::RenderWindow* window);
	
	bool initialize();

	void moveX(float x);
};

