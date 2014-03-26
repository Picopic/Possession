#include "stdafx.h"
#include "Gameplayarea.h"

#include "Spritemanager.h"
#include "AnimatedSprite.h"

Gameplayarea::Gameplayarea(void){
	sprite = nullptr;
}


Gameplayarea::~Gameplayarea(void){
	if(sprite != nullptr)
	{
		delete sprite;
		sprite = nullptr;
	}
}

sf::Vector2f Gameplayarea::getPosition(){
	return position;
}

void Gameplayarea::setPosition(sf::Vector2f pos){
	position = pos;
}

void Gameplayarea::draw(sf::RenderWindow* window){
	sprite->getSprite()->setPosition(position);
	window->draw(*sprite->getSprite());
}
	
bool Gameplayarea::initialize(const std::string Background, SpriteManager* sprite_mgr)
{
	sprite = sprite_mgr->Load("/Playarea/" + Background, 1, 1, 3650, 1080, 0, 0);
	if(sprite == nullptr)
		return false;

	return true;
}