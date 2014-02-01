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

	collider = new Collider;
	collider->position = position;
	collider->extension = Vector2(width, height);
}

void FireEnemyObject::Init(std::string object_type, Alignment enemy_alignment, Type enemy_type)
{
	entity_ID = object_type;

	alignment = enemy_alignment;
	type = enemy_type;

	shape.setSize(sf::Vector2f(width, height));
	shape.setPosition(position.x, position.y);
	
	shape.setFillColor(sf::Color(255,0,0));
	std::cout << "fireobjekt: " << position.x << std::endl;
}

void FireEnemyObject::Update(float deltatime)
{
}

void FireEnemyObject::OnCollision(Type enemy_type)
{
	std::cout << "FireObject collision" << std::endl;
}