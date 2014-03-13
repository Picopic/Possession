//SMClouds.cpp

#include "stdafx.h"
#include "SMClouds.h"


SMClouds::SMClouds(void){

}


SMClouds::~SMClouds(void){

}

sf::Vector2f SMClouds::getPosition(){
	return position;
}

void SMClouds::setPosition(sf::Vector2f pos){
	position = pos;
}

void SMClouds::draw(sf::RenderWindow* window){
	sprite.setPosition(position);

	window->draw(sprite);
}
	
bool SMClouds::initialize(){
	texture.loadFromFile("../data/f/SMClouds.png"/*, sf::IntRect(100, 200, 100, 100)*/);
	sprite.setTexture(texture);
	//sprite.setColor(sf::Color 0xff, 0xff, 0xff, 0x50);
	return true;

}

void SMClouds::moveX(float x){
	position.x += x;
}