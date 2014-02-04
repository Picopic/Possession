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

	flagged_for_death = false;
	
	collider = new Collider;
	collider->position = position;
	collider->extension = Vector2(width, height);
}

void WaterEnemyObject::Init(std::string object_type, Alignment enemy_alignment, Type enemy_type)
{
	entity_ID = object_type;

	alignment = enemy_alignment;
	type = enemy_type;

	shape.setSize(sf::Vector2f(width, height));
	shape.setPosition(position.x, position.y);
	
	shape.setFillColor(sf::Color(0,0,255));
	
	std::cout << "waterobject: " << position.x << std::endl;
}

void WaterEnemyObject::Update(float deltatime)
{
	if(hasCollider())
	{
		collider->position = position;
		shape.setPosition(position.x, position.y);
	}
}

void WaterEnemyObject::OnCollision(Type enemy_type, Vector2 offset)
{
	
}
