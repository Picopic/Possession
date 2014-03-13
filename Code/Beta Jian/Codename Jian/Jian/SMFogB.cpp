//SMFogB.cpp

#include "stdafx.h"
#include "SMFogB.h"


SMFogB::SMFogB(void){

}


SMFogB::~SMFogB(void){

}

sf::Vector2f SMFogB::getPosition(){
	return position;
}

void SMFogB::setPosition(sf::Vector2f pos){
	position = pos;
}

void SMFogB::draw(sf::RenderWindow* window){
	sprite.setPosition(position);

	window->draw(sprite);
}
	
bool SMFogB::initialize(){
	texture.loadFromFile("../data/f/SMFogB.png");
	sprite.setTexture(texture);
	//sprite.setColor(sf::Color 0xff, 0xff, 0xff, 0x50);
	return true;

}

void SMFogB::moveX(float x){
	position.x += x;
}