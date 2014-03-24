//Paralax2.cpp

#include "stdafx.h"
#include "Paralax2.h"


Paralax2::Paralax2(void){

}


Paralax2::~Paralax2(void){

}

sf::Vector2f Paralax2::getPosition(){
	return position;
}

void Paralax2::setPosition(sf::Vector2f pos){
	position = pos;
}

void Paralax2::draw(sf::RenderWindow* window){
	sprite.setPosition(position);

	window->draw(sprite);

}
	
bool Paralax2::initialize(){
	texture.loadFromFile("../data/Spritesheets/Parallax Back.png");
	sprite.setTexture(texture);

	return true;
}

void Paralax2::moveX(float x){
	position.x += x;
}