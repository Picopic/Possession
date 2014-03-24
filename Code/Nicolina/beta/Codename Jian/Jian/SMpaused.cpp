//SMpaused.cpp

#include "stdafx.h"
#include "SMpaused.h"


SMpaused::SMpaused(void){

}


SMpaused::~SMpaused(void){

}

sf::Vector2f SMpaused::getPosition(){
	return position;
}

void SMpaused::setPosition(sf::Vector2f pos){
	position = pos;
}

void SMpaused::draw(sf::RenderWindow* window){
	sprite.setPosition(position);
	window->draw(sprite);

	sprite2.setPosition(position);
	window->draw(sprite);
}
	
bool SMpaused::initialize(){
	texture.loadFromFile("../data/f/GamePausedResume.png");
	sprite.setTexture(texture);

	texture2.loadFromFile("../data/f/GamePausedQuit.png");
	sprite2.setTexture(texture2);

	return true;
}