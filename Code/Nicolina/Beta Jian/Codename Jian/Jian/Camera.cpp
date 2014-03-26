#include "stdafx.h"
#include "Camera.h"


Camera::Camera(void){

}


Camera::~Camera(void){

}

sf::Vector2f Camera::getPosition(){
	return position;
}

void Camera::setPosition(sf::Vector2f pos){
	position = pos;
}

void Camera::moveX(float x){
	position.x += x;
}
