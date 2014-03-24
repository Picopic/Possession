//Moon.cpp

#include "stdafx.h"
#include "Moon.h"


Moon::Moon(void){

}


Moon::~Moon(void){

}

sf::Vector2f Moon::getPosition(){
	return position;
}

void Moon::setPosition(sf::Vector2f pos){
	position = pos;
}

void Moon::draw(sf::RenderWindow* window){
	sprite.setPosition(position);

	window->draw(sprite);

}
	
bool Moon::initialize(){
	texture.loadFromFile("../data/f/Moon.png");
	sprite.setTexture(texture);

	return true;
}

void Moon::moveX(float x){
	position.x += x;
}