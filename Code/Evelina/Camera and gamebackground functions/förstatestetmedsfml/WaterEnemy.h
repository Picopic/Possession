//WaterEnemy.h

#pragma once
#include "stdafx.h"
#include "Player.h"

class WaterEnemy
{
private:
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Texture texture;
	sf::Sprite sprite;

	int m_random;

public:
	WaterEnemy(void);
	~WaterEnemy(void);

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);

	void draw(sf::RenderWindow* window);
	
	sf::Vector2f getVelocity();
	void setVelocity(sf::Vector2f veloc);

	bool initialize();

	void moveX(float x);
	void moveY(float y);

	void Update(Player* player);

	void CheckCollision(WaterEnemy* waterenemy);

	
};
