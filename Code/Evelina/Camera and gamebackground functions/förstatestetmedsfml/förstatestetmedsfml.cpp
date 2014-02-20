//main.cpp

#include "stdafx.h"
#include <iostream>

#include "Camera.h"
#include "Cloud.h"
#include "Gameplayarea.h"
#include "Paralax.h"
#include "Player.h"
#include "WaterEnemy.h"
#include "FireEnemy.h"
#include "WoodEnemy.h"

//för randomfunktionen:
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <ctime>

#include <vector>


using namespace sf;

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(0));
	RenderWindow* window = new RenderWindow(VideoMode(1024,640), "Caption");
	
	Camera camera;
	Cloud cloud;
	Cloud cloud2;
	Gameplayarea gameplayarea;
	Gameplayarea gameplayarea2;
	Paralax paralax;
	Player player;
	WaterEnemy waterenemy;
	FireEnemy fireenemy;
	WoodEnemy woodenemy;

	//För att det ska vara många av Waterenemy:
	std::vector<WaterEnemy*> m_WaterEnemies;
	for (int i=0; i<2; i++){ 
		m_WaterEnemies.push_back(new WaterEnemy);
		m_WaterEnemies.at(i)->initialize();
		int randomposwaterenemies = (rand()%(640-(290)+1))+(290);
		m_WaterEnemies.at(i)->setPosition(sf::Vector2f(1024, randomposwaterenemies ));
	}
	
	//För att det ska vara många av Fireenemy:
	std::vector<FireEnemy*> m_FireEnemies;
	for (int i=0; i<3; i++){ 
		m_FireEnemies.push_back(new FireEnemy);
		m_FireEnemies.at(i)->initialize();
		int randomposfireenemies = (rand()%(640-(290)+1))+(290);
		m_FireEnemies.at(i)->setPosition(sf::Vector2f(1024, randomposfireenemies ));
	}
	//För att det ska vara många av Woodenemy:
	std::vector<WoodEnemy*> m_WoodEnemies;
	for (int i=0; i<5; i++){ 
		m_WoodEnemies.push_back(new WoodEnemy);
		m_WoodEnemies.at(i)->initialize();
		int randomposwoodenemies = (rand()%(640-(290)+1))+(290);
		m_WoodEnemies.at(i)->setPosition(sf::Vector2f(1024, randomposwoodenemies ));
	}

	//camera.initialize();
	camera.setPosition(sf::Vector2f(1024/2, 640/2));
		
	cloud.setPosition(sf::Vector2f(0, 0));
	cloud.initialize();

	cloud2.setPosition(sf::Vector2f(1280,0));
	cloud2.initialize();

	gameplayarea.setPosition(sf::Vector2f(0, 0));
	gameplayarea.initialize();

	gameplayarea2.setPosition(sf::Vector2f(2560, 0));
	gameplayarea2.initialize();

	paralax.setPosition(sf::Vector2f(-150, 0));
	paralax.initialize();

	//Man kanske kan göra waterenemyns position random inom vissa gränser? Kanske antal också?:
	//waterenemy.setPosition(sf::Vector2f(1024, int random= sf::Randomizer::Random(630/2, 630));
	/*int randomtal = (rand()%(640-(290)+1))+(290);
	waterenemy.setPosition(sf::Vector2f(1024, randomtal));
	waterenemy.initialize();
	std::cout << randomtal << std::endl;*/

	player.setPosition(sf::Vector2f(1024/2, 640/2));
	player.initialize();
	
	sf::View view(sf::Vector2f(0,0), sf::Vector2f(1024,640));
	
	while (window->isOpen()) {
		Event event;
		while(window->pollEvent(event)) {
			if(event.type == Event::Closed) {
				window->close();
			};
		};

		//And here comes the player movement
		if(Keyboard::isKeyPressed(Keyboard::Escape)) {
			window->close();
		};
		
		
		if(Keyboard::isKeyPressed(Keyboard::W)) {
			player.moveY(-0.8);
			//kan inte gå över horisontlinjen:
			if (player.getPosition().y < 240){
				sf::Vector2f vect = player.getPosition();
				vect.y = 240;
				player.setPosition(vect);
			};
		};

		if(Keyboard::isKeyPressed(Keyboard::A)) {
			player.moveX(-0.4);

			//kan inte gå ur vänster vägg:
			if (player.getPosition().x < 50){
				sf::Vector2f vect = player.getPosition();
				vect.x = 50;
				player.setPosition(vect);
			};
		};

		if(Keyboard::isKeyPressed(Keyboard::S)) {
			player.moveY(+0.8);
			//kan inte gå under nedre kant:
			if (player.getPosition().y > 640-65){
				sf::Vector2f vect = player.getPosition();
				vect.y = 640-65;
				player.setPosition(vect);
			};
		};

		if(Keyboard::isKeyPressed(Keyboard::D)) {
			player.moveX(+0.4);

			//kan inte gå ur höger vägg:
			if (player.getPosition().x > 2485+2560){
				sf::Vector2f vect = player.getPosition();
				vect.x = 2485+2560;
				player.setPosition(vect);
			}
			
		};

		
		//Camera focus/movement:
		//kameran ska dock inte kunna visa vad som finns utanför banan åt höger(banans slut):
		//OBS MYCKET VIKTIGT MED > OCH = TILLSAMMANS
		if (camera.getPosition().x >= 2042+2560){
			sf::Vector2f vect = camera.getPosition();
			vect.x = 2042+2560;
			camera.setPosition(vect);
		}

		//hur långt inann kameran hänger med åt höger:
		else if (camera.getPosition().x < player.getPosition().x - 70){
			sf::Vector2f vect = camera.getPosition();
			vect.x = player.getPosition().x - 70;
			camera.setPosition(vect);

			//molnens position accelererar el saktas ner beroende åt vilket håll man går:
			cloud.moveX (0.3);
			cloud2.moveX (0.3);
			//cloud2.getPosition().x + 0.3;
			//background2 position:
			paralax.moveX(0.3);
		}
		
		//std::cout << camera.getPosition().x << " " << player.getPosition().x << std::endl;
		//kameran ska inte kunna visa vad som finns utanför banan åt vänster(banans början):
		if (camera.getPosition().x <= 512){
			sf::Vector2f vect = camera.getPosition();
			vect.x = 512;
			camera.setPosition(vect);
		}

		//hur långt innan kameran hänger med åt vänster
		else if (camera.getPosition().x > player.getPosition().x + 300){
			sf::Vector2f vect = camera.getPosition();
			vect.x = player.getPosition().x + 300;
			camera.setPosition(vect);

			//molnens position accelererar el saktas ner beroende åt vilket håll man går:
			cloud.moveX (-0.34);
			cloud2.moveX (-0.34);
			//background2 position:
			paralax.moveX(-0.3);
			}
		
		//Molnens position och rörelser:
		if(cloud.getPosition().x <= camera.getPosition().x - 1280 - 512){
			sf::Vector2f vect = cloud.getPosition();
			vect.x = camera.getPosition().x + 512;
			cloud.setPosition(vect);
		}
		if(cloud2.getPosition().x <= camera.getPosition().x - 1280 - 512){
			sf::Vector2f vect = cloud2.getPosition();
			vect.x = camera.getPosition().x + 512;
			cloud2.setPosition(vect);
		}

		cloud.moveX(-0.05);
		cloud2.moveX(-0.05);
		

		//Enemies update:::::
		for (int i = 0; i<m_WaterEnemies.size(); i++){
			m_WaterEnemies.at(i)->Update(&player);
			for (int j = 0; j<m_WaterEnemies.size(); j++){
				if (i!=j){
				//här är collisioncheck;
				m_WaterEnemies.at(i)->CheckCollision(m_WaterEnemies.at(j));
				}
			}
		}
		for (int i = 0; i<m_FireEnemies.size(); i++){
			m_FireEnemies.at(i)->Update(&player);
		}
		for (int i = 0; i<m_WoodEnemies.size(); i++){
			m_WoodEnemies.at(i)->Update(&player);
		}




		view.setCenter(camera.getPosition());
		window->setView(view);

		window->clear(sf::Color(0x80, 0x80, 0x80, 0xff));

		cloud.draw(window);
		cloud2.draw(window);
		paralax.draw(window);

		//HUR SPELPLANERNA SPAWNAR
		//kommer fixa så att man kan köra delete på dom senare när dom är pekare så blir allt perfa:
		//spelplan1
		if (player.getPosition().x >= 0 && player.getPosition().x <= 3840){
				gameplayarea.draw(window);
			};
		
		//För att nästa spelplansdel inte ska spawna förrän man går dit:
		if (player.getPosition().x >= 1280 && player.getPosition().x <= 6400){
				gameplayarea2.draw(window);
			};
			
		for(int i = 0; i<m_WaterEnemies.size(); i++){
		m_WaterEnemies.at(i)->draw(window);
		}

		for(int i = 0; i<m_FireEnemies.size(); i++){
		m_FireEnemies.at(i)->draw(window);
		}

		for(int i = 0; i<m_WoodEnemies.size(); i++){
		m_WoodEnemies.at(i)->draw(window);
		}

		player.draw(window);

		window->display();

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

/*
	Klasser:
	Spelaren
	Kameran
	Gameplay area
	Moln
	Moln2
	Övrig paralax
*/

