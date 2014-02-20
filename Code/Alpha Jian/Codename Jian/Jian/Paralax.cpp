#include "stdafx.h"
#include "Paralax.h"


Paralax::Paralax(void){

}


Paralax::~Paralax(void){

}

sf::Vector2f Paralax::getPosition(){
	return position;
}

void Paralax::setPosition(sf::Vector2f pos){
	position = pos;
}

void Paralax::draw(sf::RenderWindow* window){
	sprite.setPosition(position);

	window->draw(sprite);

}
	
bool Paralax::initialize(){
	texture.loadFromFile("../data/Spritesheets/Parallax Front.png");
	sprite.setTexture(texture);

	return true;
}

void Paralax::moveX(float x){
	position.x += x;
}