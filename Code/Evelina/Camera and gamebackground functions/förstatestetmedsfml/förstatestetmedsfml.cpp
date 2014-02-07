//main.cpp

#include "stdafx.h"
#include <iostream>

using namespace sf;

int _tmain(int argc, _TCHAR* argv[])
{
	RenderWindow window(VideoMode(1024,640), "Caption");
	
	//CircleShape will be the player moving around.
	CircleShape shape (30.0f);

	//Kamerans fokus:
	CircleShape shape3(10.0f);
	
	//Bakgrundsmark:
	Texture Ibackground;
	Sprite background;

	Ibackground.loadFromFile("../bin/BG.png");
	background.setTexture(Ibackground);
	background.setPosition(0, 0);

	//Bakgrundshorisontgrejs:
	Texture Ibackground2;
	Sprite background2;
	
	Ibackground2.loadFromFile("../bin/BG2.png");
	background2.setTexture(Ibackground2);
	background2.setPosition(0,0);
	

	//playerxaxe playeryaxe är för spelaren
	//cameraXaxe cameraYaxe är för kameran
	//couldXaxe är för molnen
	float playerXaxe, playerYaxe, cameraXaxe , cameraYaxe, cloudXaxe, background2Xaxe; //axis
	//Spelarens koordinater
	//playerXaxe=x-led, playerYaxe=y-led
	playerXaxe=1024/2;
	playerYaxe=640/2;
	//Kamerans koordinater
	//cameraXaxe=x-led, cameraYaxe=y-led
	//cameraYaxe ska dock aldrig ändras(en konstant)
	cameraXaxe=1024/2;
	cameraYaxe=640/2;
	//molnkoordinater cloudXaxe-led:
	//y-led ska aldrig ändras
	cloudXaxe=0;
	//bakgrundskoordinater:
	background2Xaxe=0;

	//Moln:
	Texture Imoln;
	Sprite moln;
	Imoln.loadFromFile("../bin/M.png");
	moln.setTexture(Imoln);

	
	//Måste göra så att de upprepas efter ett tag då de ska scrolla i bakgrunden
	//Molnen kommer ur programmeringssynopunkt ej flyttas åt motsatt håll som spelaren, utan åt samma fast väldigt långsamt.

	//for the camera:
	bool left=false;
	
	//kameravektorer:
	sf::View view(sf::Vector2f(0,0), sf::Vector2f(1024,640)) ;

	//Set.Origin is where the middle on Sven is.
	//Set.Position tells Sven where on the screen to start off.
	shape.setFillColor(Color(0x99, 0x30, 0x70, 0xff));
	shape.setOutlineColor(Color(0x80, 0x20, 0x50, 0xff));
	shape.setOutlineThickness(5.0f);
	shape.setOrigin((30/2), (30/2));
	shape.setPosition(playerXaxe, playerYaxe);
	

	//Position and origin for the middle- camera- dot- shape
	shape3.setFillColor(Color(0x99, 0x30, 0x70, 0xff));
	shape3.setOutlineColor(Color(0x80, 0x20, 0x50, 0xff));
	shape3.setOutlineThickness(5.0f);
	shape3.setOrigin((10/2), (10/2));
	shape3.setPosition(cameraXaxe, cameraYaxe);
	
	int index = 0;

	while (window.isOpen()) {
		Event event;
		while(window.pollEvent(event)) {
			if(event.type == Event::Closed) {
				window.close();
			};
		};

		//And here comes the player movement
		if(Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		};

		if(Keyboard::isKeyPressed(Keyboard::W)) {
			playerYaxe-=0.4;
			//kan inte gå över horisontlinjen:
			if (playerYaxe<(253+21)){
				playerYaxe=(253+21);
			};
		};
		if(Keyboard::isKeyPressed(Keyboard::A)) {
			playerXaxe-=0.4;
			//q-=0.2;
			//camera:
			left=true;
			//molnens koordinater mx:
			//mx-=0.1;
			//kan inte gå ur vänster vägg:
			if (playerXaxe<(0+48)){
			playerXaxe=(0+48);
			};
		};
		if(Keyboard::isKeyPressed(Keyboard::S)) {
			playerYaxe+=0.4;
			//kan inte gå under nedre kanten:
			if (playerYaxe>(640-50)){
			playerYaxe=(640-50);
			};
		};
		if(Keyboard::isKeyPressed(Keyboard::D)) {
			playerXaxe+=0.4;
			//q+=0.2;
			//camera:
			left=false;
			//molnens koordinater mx:
			//mx+=0.1;
			//kan inte gå utanför högra kanten:
			if (playerXaxe>2468){
			playerXaxe=2468;
			}
		};

		//Camera focus/movement:
		//kameran ska dock inte kunna visa vad som finns utanför banan åt höger:
		//OBS MYCKET VIKTIGT MED > OCH = TILLSAMMANS
		if (cameraXaxe>=2042){
			cameraXaxe=2042;
		}

		//hur långt inann kameran hänger med åt höger:
		else if (cameraXaxe<(playerXaxe-70)){
			cameraXaxe=(playerXaxe-70);
			//molnens position
			cloudXaxe+=0.35;
			//background2 position:
			background2Xaxe+=0.30;
		}

		//kameran ska inte kunna visa vad som finns utanför banan åt vänster:
		if (cameraXaxe<=512){
				cameraXaxe=(512);
		}

		//hur långt innan kameran hänger med åt vänster
		else if (cameraXaxe>(playerXaxe+300)){
			cameraXaxe=(playerXaxe+300);
			//molnens position:
			cloudXaxe-=0.35;
			//background2 position:
			background2Xaxe-=0.30;
		};

		std::cout << cameraXaxe << " " << cameraYaxe << std::endl;

		//kamerans förhållande till spelaren lr ngt:
		view.setCenter(sf::Vector2f(cameraXaxe, cameraYaxe));
		window.setView(view);

		window.clear(Color(0x99, 0x99, 0x99, 0xff));
		shape.setPosition(playerXaxe, playerYaxe);
		shape3.setPosition(cameraXaxe, cameraYaxe);
		moln.setPosition(cloudXaxe,0);
		background2.setPosition(background2Xaxe,0);

		window.draw(moln);
		window.draw(background2);
		window.draw(background);

		window.draw(shape);
		window.draw(shape3);
		window.display();
		
	};
	return 0;
};

/**
	StateManager
	InputManager
	SpriteManager
	AudioManager
	CollisionManager
	GameObjectManager / EntityManager
	DrawManager

	SpriteManager
	Sprite

	UML - google it

*/

