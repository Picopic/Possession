//FireEnemyObject

#include "stdafx.h"

#include "FireEnemyObject.h"

FireEnemyObject::FireEnemyObject()
{

}

FireEnemyObject::FireEnemyObject(Vector2 enemy_position, int enemy_width, int enemy_height)
{
	position = enemy_position;
	width = enemy_width;
	height = enemy_height;
}

void FireEnemyObject::Init(std::string object_type)
{
	entity_ID = object_type;
	//shape.setRadius(width);
	//shape.setPosition(position.x, position.y);
	
	//shape.setFillColor(sf::Color(255,0,0));
	std::cout << "fireobjekt: " << position.x << std::endl;
}

void FireEnemyObject::Update(float deltatime)
{

}