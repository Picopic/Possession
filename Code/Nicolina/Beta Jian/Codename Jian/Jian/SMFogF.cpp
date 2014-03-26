//SMFogF.cpp

#include "stdafx.h"
#include "SMFogF.h"


SMFogF::SMFogF(void){

}


SMFogF::~SMFogF(void){

}

sf::Vector2f SMFogF::getPosition(){
	return position;
}

void SMFogF::setPosition(sf::Vector2f pos){
	position = pos;
}

void SMFogF::draw(sf::RenderWindow* window){
	sprite.setPosition(position);

	window->draw(sprite);
}
	
bool SMFogF::initialize(){
	texture.loadFromFile("../data/f/SMFogF.png");
	sprite.setTexture(texture);
	//sprite.setColor(sf::Color 0xff, 0xff, 0xff, 0x50);
	return true;

}

void SMFogF::moveX(float x){
	position.x += x;
}