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

	flagged_for_death = false;

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

	std::cout << "Fireenemy objekt x: " << position.x << "\tFireenemy objekt y: " << position.y << std::endl;
	std::cout << "Fireenemy collider x: " << collider->position.x << "\tFireenemy collider y: " << collider->position.y << std::endl;

	shape.setFillColor(sf::Color(255,0,0));
	std::cout << "fireobjekt: " << position.x << std::endl;
}

void FireEnemyObject::Update(float deltatime)
{
	if(hasCollider())
	{
		position = collider->position;
		shape.setPosition(position.x, position.y);
	}
}

void FireEnemyObject::OnCollision(Type enemy_type, Vector2 offset)
{
}