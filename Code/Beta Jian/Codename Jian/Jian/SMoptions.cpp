//SMoptions.cpp

#include "stdafx.h"
#include "SMoptions.h"
#include "Spritemanager.h"
#include "SMslider.h"

SMoptions::SMoptions(){
	smslider1= new SMslider("soundlevel", sf::Vector2f(1480,310),50); 

	smslider2= new SMslider("soundlevel", sf::Vector2f(1480,480),50); 

	smslider3= new SMslider("soundlevel", sf::Vector2f(1480,640),50);

	texture3.loadFromFile("../data/f/SMoptionsejon.png");
	texture4.loadFromFile("../data/f/SMoptionsvald.png");

	onoff.setTexture(texture3);
	onoff.setOrigin(onoff.getLocalBounds().width/2, onoff.getLocalBounds().height/2);
	onoff.setPosition(1640, 780);

	vald.setTexture(texture4);
	vald.setOrigin(vald.getLocalBounds().width/2, vald.getLocalBounds().height/2);
	vald.setPosition(1480,310);
	//onoff=new SMslider("fullscreen", sf::Vector2f(1640, 780), 50);
	//vald =new SMslider ("vald", sf::Vector2f(1480,310),50);
}


SMoptions::~SMoptions(void){

	delete smslider1;
	smslider1 = nullptr;

	delete smslider2;
	smslider2 = nullptr;

	delete smslider3;
	smslider3 = nullptr;

	////delete onoff;
	//onoff =nullptr;

	//delete vald;
	//vald =nullptr;

}

sf::Vector2f SMoptions::getPosition(){
	return position;
}

void SMoptions::setPosition(sf::Vector2f pos){
	position = pos;
}

void SMoptions::draw(sf::RenderWindow* window){

	sprite.setPosition(position);
	window->draw(sprite);

	window->draw(*smslider1->GetSliderSprite2());
	window->draw(*smslider2->GetSliderSprite2());
	window->draw(*smslider3->GetSliderSprite2());

	window->draw(*smslider1->GetSliderSprite());
	window->draw(*smslider2->GetSliderSprite());
	window->draw(*smslider3->GetSliderSprite());

	window->draw(vald);
	window->draw(onoff);
	//window->draw(*vald->GetvaldSprite());

	//window->draw(*onoff->GetonoffSprite());
}

bool SMoptions::initialize(SpriteManager* spritemanager){



	texture.loadFromFile("../data/Spritesheets2/SMoptionsstatic.png");
	sprite.setTexture(texture);

	return true;
}