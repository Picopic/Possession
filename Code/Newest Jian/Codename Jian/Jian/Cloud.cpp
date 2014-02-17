#include "stdafx.h"
#include "Cloud.h"


Cloud::Cloud(void){

}


Cloud::~Cloud(void){

}

sf::Vector2f Cloud::getPosition(){
	return position;
}

void Cloud::setPosition(sf::Vector2f pos){
	position = pos;
}

void Cloud::draw(sf::RenderWindow* window){
	sprite.setPosition(position);

	window->draw(sprite);
}
	
bool Cloud::initialize(){
	texture.loadFromFile("../data/background/M.png");
	sprite.setTexture(texture);
	return true;

}

void Cloud::moveX(float x){
	position.x += x;
}