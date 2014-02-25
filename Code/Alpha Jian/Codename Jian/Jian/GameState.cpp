//GameState.cpp
//Where you play the game. Enter this state from the StartMenuState.

#include "stdafx.h"
#include "GameState.h"
#include "Vector2.h"
//#include "StateMain.cpp"


GameState::GameState(sf::RenderWindow* GameWindow){
	m_window = GameWindow;
}

GameState::~GameState(){

}

bool GameState::Initialize(){

	camera.setPosition(sf::Vector2f(1024/2, 640/2));
	cameras_last_position = camera.getPosition();
		
	cloud.setPosition(sf::Vector2f(0, 0));
	cloud.initialize();

	cloud2.setPosition(sf::Vector2f(1280,0));
	cloud2.initialize();

	gameplayarea.setPosition(sf::Vector2f(0, 0));
	gameplayarea.initialize();

	gameplayarea2.setPosition(sf::Vector2f(2560, 0));
	gameplayarea2.initialize();

	paralax.setPosition(sf::Vector2f(-150, -15));
	paralax.initialize();

	paralax2.setPosition(sf::Vector2f(-150, +50));
	paralax2.initialize();

	//player.setPosition(sf::Vector2f(1024/2, 640/2));
	//player.initialize();
	
	m_view.setCenter(camera.getPosition());
	m_view.setSize(sf::Vector2f(1024,640));

	draw_manager = new DrawManager;
	
	sound_manager = new SoundManager;
	sound_manager->Initialise("../data/Sound/");

	sprite_manager = new SpriteManager;
	sprite_manager->Initialise("../data/Spritesheets/");

	HUD = new HeadsUpDisplay;
	if(!HUD->Initialise(sprite_manager))
	{
		return false;
	}

	for(int i = 0; i < 3; i++)
	{
		HUD->AddElementalPoint(FIRE);
	}
	for(int i = 0; i < 3; i++)
	{
		HUD->AddElementalPoint(WATER);
	}
	for(int i = 0; i < 3; i++)
	{
		HUD->AddElementalPoint(WOOD);
	}
	
	entity_manager = new EntityManager(sprite_manager, sound_manager);
	entity_manager->Init();
	entity_manager->AttachEntity(PLAYER, Vector2(0, 300), 50, 110, FIRE);
	entity_manager->AttachEntity(FIREFOE, Vector2(600, 200), 100, 80, FIRE);

	previous_time = game_clock.restart();
	deltatime = 0.01f;
	
	//music
	if(!background_music.openFromFile("../data/Sound/wizhit.wav"))
	{
		return false;
	}

	m_done = false;
	return false;

	
}

bool GameState::Enter(){

	std::cout << "Welcome to the GameState" << std::endl;
	std::cout << "Press 4 to go back to StartMenuState" <<std::endl;
	return false;
}

bool GameState::Exit(){
	return false;
}

bool GameState::Update(){

	m_done = false;
	UpdateDeltatime();

		//while (window->isOpen()) {
		sf::Event event;
		while(m_window->pollEvent(event)) {
			if(event.type == sf::Event::Closed) {
				m_window->close();
			};
		};

		//player related HUD changes
		if(entity_manager->game_entities[0]->getAlignment() == PLAYER)
		{
			if(entity_manager->game_entities[0]->ChangedElement())
			{
				HUD->MoveArrow(entity_manager->game_entities[0]->GetArrow());
			}

			//Add element points?
			if(entity_manager->game_entities[0]->AddElementPoints())
			{
				if(entity_manager->game_entities[0]->GetAddFire() > 0)
				{
					for(int i = 0; i < entity_manager->game_entities[0]->GetAddFire(); i++)
					{
						HUD->AddElementalPoint(FIRE);
					}
				}
				if(entity_manager->game_entities[0]->GetAddWater() > 0)
				{
					for(int i = 0; i < entity_manager->game_entities[0]->GetAddWater(); i++)
					{
						HUD->AddElementalPoint(WATER);
					}
				}
				if(entity_manager->game_entities[0]->GetAddWood() > 0)
				{
					for(int i = 0; i < entity_manager->game_entities[0]->GetAddWood(); i++)
					{
						HUD->AddElementalPoint(WOOD);
					}
				}
			}
			//Delete element points?
			if(entity_manager->game_entities[0]->DeleteElementPoints())
			{
				if(entity_manager->game_entities[0]->GetDestroyFire() > 0)
				{
					for(int i = 0; i < entity_manager->game_entities[0]->GetDestroyFire(); i++)
					{
						HUD->DeleteElementalPoint(FIRE);
					}
				}
				else if(entity_manager->game_entities[0]->GetDestroyWater() > 0)
				{
					for(int i = 0; i < entity_manager->game_entities[0]->GetDestroyWater(); i++)
					{
						HUD->DeleteElementalPoint(WATER);
					}
				}
				else if(entity_manager->game_entities[0]->GetDestroyWood() > 0)
				{
					for(int i = 0; i < entity_manager->game_entities[0]->GetDestroyWood(); i++)
					{
						HUD->DeleteElementalPoint(WOOD);
					}
				}
			}
		}

		//And here comes the player movement
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			m_window->close();
		};
		
			//kan inte gå över horisontlinjen:
			if (entity_manager->game_entities.at(0)->getPosition().y < 240){
				Vector2 vect (entity_manager->game_entities.at(0)->getPosition());
				vect.y = 240;
				entity_manager->game_entities.at(0)->setPosition(vect);
			};

			//kan inte gå ur vänster vägg:
			if (entity_manager->game_entities.at(0)->getPosition().x < 50){
				Vector2 vect (entity_manager->game_entities.at(0)->getPosition());
				vect.x = 50;
				entity_manager->game_entities.at(0)->setPosition(vect);
			};

			//kan inte gå under nedre kant:
			if (entity_manager->game_entities.at(0)->getPosition().y > 450){
				Vector2 vect (entity_manager->game_entities.at(0)->getPosition());
				vect.y = 450;
				entity_manager->game_entities.at(0)->setPosition(vect);
			};

			//kan inte gå ur höger vägg:
			if (entity_manager->game_entities.at(0)->getPosition().x > 2485+2560){
				Vector2 vect (entity_manager->game_entities.at(0)->getPosition());
				vect.x = 2485+2560;
				entity_manager->game_entities.at(0)->setPosition(vect);
			}
			

		
		//Camera focus/movement:
		//kameran ska dock inte kunna visa vad som finns utanför banan åt höger(banans slut):
		//OBS MYCKET VIKTIGT MED > OCH = TILLSAMMANS
		if (camera.getPosition().x >= 2042+2560){
			sf::Vector2f vect = camera.getPosition();
			vect.x = 2042+2560;
			camera.setPosition(vect);
		}

		//hur långt inann kameran hänger med åt höger:
		else if (camera.getPosition().x < entity_manager->game_entities.at(0)->getPosition().x - 70){
			sf::Vector2f vect = camera.getPosition();
			vect.x = entity_manager->game_entities.at(0)->getPosition().x - 70;
			camera.setPosition(vect);

			//molnens position accelererar el saktas ner beroende åt vilket håll man går:
			cloud.moveX (0.08);
			cloud2.moveX (0.08);
			//cloud2.getPosition().x + 0.3;
			//background2 position:
			paralax.moveX(0.07);
			paralax2.moveX(0.1);
		}
		
		//std::cout << camera.getPosition().x << " " << player.getPosition().x << std::endl;
		//kameran ska inte kunna visa vad som finns utanför banan åt vänster(banans början):
		if (camera.getPosition().x <= 512){
			sf::Vector2f vect = camera.getPosition();
			vect.x = 512;
			camera.setPosition(vect);
		}

		//hur långt innan kameran hänger med åt vänster
		else if (camera.getPosition().x > entity_manager->game_entities.at(0)->getPosition().x + 300){
			sf::Vector2f vect = camera.getPosition();
			vect.x = entity_manager->game_entities.at(0)->getPosition().x + 300;
			camera.setPosition(vect);

			//molnens position accelererar el saktas ner beroende åt vilket håll man går:
			cloud.moveX (-0.15);
			cloud2.moveX (-0.15);
			//cloud2.getPosition().x + 0.3;
			//background2 position:
			paralax.moveX(-0.1);
			paralax2.moveX(-0.15);
			}
		
		
		//std::cout << cloudXaxe << std::endl;

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

		
		/*
		if(playerXaxe>=1280 && playerXaxe<=6400){		
			window.draw(background3);
			std::cout << "Bla bakgrund framme" << std::endl;
		}

		window.draw(shape3);
		window.draw(shape);
		
		window.display();
	*/	
		
		m_view.setCenter(camera.getPosition());
		m_window->setView(m_view);



		m_window->clear(sf::Color(0x40, 0x20, 0x30, 0xff));

		paralax2.draw(m_window);		

		cloud.draw(m_window);
		cloud2.draw(m_window);
		
		paralax.draw(m_window);
		

		
		//kommer fixa så att man kan köra delete på dom senare när dom är pekare så blir allt perfa:
		//spelplan1
		if (entity_manager->game_entities.at(0)->getPosition().x >= 0 && entity_manager->game_entities.at(0)->getPosition().x <= 3840){
				gameplayarea.draw(m_window);
				//std::cout << "Gra bakgrund framme" << std::endl;
			};
		
		//För att nästa spelplansdel inte ska spawna förrän man går dit:
		if (entity_manager->game_entities.at(0)->getPosition().x >= 1280 && entity_manager->game_entities.at(0)->getPosition().x <= 6400){
				gameplayarea2.draw(m_window);
				//std::cout << gameplayarea2.getPosition().x << std::endl;
			};
			
		HUD->Move((camera.getPosition().x-cameras_last_position.x), 0);
		cameras_last_position = camera.getPosition();

		entity_manager->Update(deltatime);

		//drawing portion of game loop
		draw_manager->Draw(m_window, entity_manager, HUD);

	//};

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
		m_next_state = "StartMenuState";
		m_done=true;
		
	};
	return m_done;
}

std::string GameState::Next(){
	return m_next_state;
}

bool GameState::IsType(const std::string& Type){
	return Type == "GameState";
}

bool GameState::Draw(){
	//m_window->clear(Color(0x55, 0x99, 0xff, 0xff));
	//m_window->display();
	return false;
}

void GameState::UpdateDeltatime(){
	sf::Time temp_time;
	temp_time = game_clock.getElapsedTime();
	deltatime = (temp_time.asSeconds() - previous_time.asSeconds());
	previous_time = temp_time;
}