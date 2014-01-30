//WaterEnemyObject.cpp

#include "stdafx.h"

#include "WaterEnemyObject.h"

WaterEnemyObject::WaterEnemyObject()
{

}

WaterEnemyObject::WaterEnemyObject(Vector2 enemy_position, int enemy_width, int enemy_height)
{
	position = enemy_position;
	width = enemy_width;
	height = enemy_height;
}

void WaterEnemyObject::Init(std::string object_type)
{
	entity_ID = object_type;
	//shape.setRadius(width);
	//shape.setPosition(position.x, position.y);
	
	//shape.setFillColor(sf::Color(0,0,255));
	std::cout << "waterobject: " << position.x << std::endl;
}

void WaterEnemyObject::Update(float deltatime)
{

}