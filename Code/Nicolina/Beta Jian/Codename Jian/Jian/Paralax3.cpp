//Paralax3.cpp
//Gräs i förgrunden

#include "stdafx.h"
#include "Paralax3.h"


Paralax3::Paralax3(void){

}


Paralax3::~Paralax3(void){

}

sf::Vector2f Paralax3::getPosition(){
	return position;
}

void Paralax3::setPosition(sf::Vector2f pos){
	position = pos;
}

void Paralax3::draw(sf::RenderWindow* window){
	sprite.setPosition(position);

	window->draw(sprite);

}
	
bool Paralax3::initialize(){
	texture.loadFromFile("../data/Spritesheets/L1.png");
	sprite.setTexture(texture);

	return true;
}

void Paralax3::moveX(float x){
	position.x += x;
}