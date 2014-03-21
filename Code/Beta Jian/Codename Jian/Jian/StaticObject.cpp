//StaticObject.cpp

#include "stdafx.h"

#include "StaticObject.h"

//---------------------Constructors and Deconstructors-------------------------//
StaticObject::StaticObject()
{

}

StaticObject::StaticObject(ConfigManager* ConfigMgr, Vector2 Position, std::string Object)
{
	//Position of the objects
	position = Position;
	StaticPosition = position;

	//Set properties
	width = ConfigMgr->ReadInt(Object + "Width");
	height = ConfigMgr->ReadInt(Object + "Height");

	entity_offset_x = ConfigMgr->ReadInt(Object + "OffsetX");
	entity_offset_y = ConfigMgr->ReadInt(Object + "OffsetY");
	can_collide = true;

	//Collision
	collider = new Collider;
	collider->position.x = position.x + entity_offset_x;
	collider->position.y = position.y + entity_offset_y;
	collider->extension = Vector2(width, height);

	hitbox.setSize(sf::Vector2f(width, height));
	hitbox.setOrigin(0, 0);
	hitbox.setPosition(collider->position.x, collider->position.y);
	hitbox.setFillColor(sf::Color(0,0,0,0));
	hitbox.setOutlineThickness(1);
	hitbox.setOutlineColor(sf::Color(255,0,0,255));

	//State
	flagged_for_death = false;
	dead = false;
}
//----------------------End of Constructors and Deconstructors-----------------//

//----------------------Essential Inherited Functions--------------------------//
void StaticObject::Init(std::string Object, Alignment ObjectAlignment, Type ObjectType)
{
	alignment = ObjectAlignment;
	type = ObjectType;
}

void StaticObject::Update(float Deltatime)
{

}

void StaticObject::OnCollision(Entity* CollisionEntity,Type CollisionType, Vector2 Offset, Alignment EnemyAlignment)
{
	
}
//---------------------End of Essential Inherited Functions-------------------//