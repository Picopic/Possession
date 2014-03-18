//GameState.cpp
//Where you play the game. Enter this state from the StartMenuState.

#include "stdafx.h"
#include "GameState.h"
#include "Vector2.h"
//#include "StateMain.cpp"


GameState::GameState(sf::RenderWindow* GameWindow){
	m_window = GameWindow;
	Pause = true;
	StartPauseTimer = false;
	PauseTimer = 0.0f;
}

GameState::~GameState(){
	if(m_window != nullptr)
	{
		m_window = nullptr;
	}

	if(draw_manager != nullptr)
	{
		delete draw_manager;
		draw_manager = nullptr;
	}

	if(sprite_manager != nullptr)
	{
		delete sprite_manager;
		sprite_manager = nullptr;
	}

	if(entity_manager != nullptr)
	{
		delete entity_manager;
		entity_manager = nullptr;
	}

	if(HUD != nullptr)
	{
		delete HUD;
		HUD = nullptr;
	}

	if(sound_manager != nullptr)
	{
		delete sound_manager;
		sound_manager = nullptr;
	}

	if(config_manager != nullptr)
	{
		config_manager = nullptr;
	}

	if(enemy_waves != nullptr)
	{
		delete enemy_waves;
		enemy_waves = nullptr;
	}
}

bool GameState::Initialize(){
	
	PauseTimer = 0.0f;

	camera.setPosition(sf::Vector2f(1920/2, 1080/2));
	cameras_last_position = camera.getPosition();
		
	cloud.setPosition(sf::Vector2f(0, 0));
	cloud.initialize();

	cloud2.setPosition(sf::Vector2f(3840,0));
	cloud2.initialize();

	gameplayarea.setPosition(sf::Vector2f(0, 0));
	gameplayarea.initialize();

	gameplayarea2.setPosition(sf::Vector2f(3619, 0));
	gameplayarea2.initialize();

	paralax1.setPosition(sf::Vector2f(-150, -15+90));
	paralax1.initialize();
	paralax11.setPosition(sf::Vector2f(3850, -15+90));
	paralax11.initialize();

	paralax2.setPosition(sf::Vector2f(-150, +50+70));
	paralax2.initialize();
	paralax22.setPosition(sf::Vector2f(3354, +50+70));
	paralax22.initialize();

	//gräsparallax:
	paralax3.setPosition(sf::Vector2f(-50, +1080-65));
	paralax3.initialize();
	paralax33.setPosition(sf::Vector2f(+3150, +1080-65));
	paralax33.initialize();
	
	m_view.setCenter(camera.getPosition());
	m_view.setSize(sf::Vector2f(1920,1080));

	draw_manager = new DrawManager;
	
	sound_manager = new SoundManager;
	sound_manager->Initialise("../data/Sound/");

	sprite_manager = new SpriteManager;
	sprite_manager->Initialise("../data/Spritesheets2/");

	//Precache the resources
	sprite_manager->LoadTexture("MC SPRITESHEET 252p w transparency.png");
	sprite_manager->LoadTexture("WATER SPRITESHEET 315p.png");
	sprite_manager->LoadTexture("FIRE SPRITESHEET 315p.png");
	sprite_manager->LoadTexture("WOOD SPRITESHEET 495x405p.png");
	sprite_manager->LoadTexture("Projectile Spritesheet Small.png");
	sprite_manager->LoadTexture("Lost Souls Spritesheet.png");

	HUD = new HeadsUpDisplay;
	if(!HUD->Initialise(sprite_manager))
	{
		return false;
	}
	
	entity_manager = new EntityManager(sprite_manager, sound_manager);

	config_manager = new ConfigManager;
	config_manager->Initialise("../data/Configs/");
	config_manager->ReadFile("Config.txt");
	config_manager->ReadFile("Enemywaves.txt");

	enemy_waves = new EnemyWaves(entity_manager, config_manager);

	entity_manager->Init(enemy_waves);
	entity_manager->AttachEntity(PLAYER, Vector2(0, 300), FIRE);

	previous_time = game_clock.restart();
	deltatime = 0.01f;
	
	//music
	//if(!background_music.openFromFile("../data/Sound/wizhit.wav"))
	//{
	//	return false;
	//}

	m_done = false;

	draw_hitbox = false;

	return true;
}

bool GameState::Enter(){

	std::cout << "Welcome to the GameState" << std::endl;
	std::cout << "Press 4 to go back to StartMenuState" <<std::endl;

	UpdateDeltatime();

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
		if(m_window->pollEvent(event)) {
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
			{
				if(draw_hitbox)
					draw_hitbox = false;
				else
					draw_hitbox = true;
			}
		};

		//player related HUD changes
		if(entity_manager->game_entities[0]->getAlignment() == PLAYER)
		{
			if(entity_manager->game_entities[0]->ChangedElement())
			{
				HUD->MoveIndicator(entity_manager->game_entities[0]->GetArrow());
			}

			if(entity_manager->game_entities[0]->AddSoul())
				HUD->AddSoul();
			else if(entity_manager->game_entities[0]->DeleteSoul())
				HUD->DeleteSoul();

			//Add element points?
			if(entity_manager->game_entities[0]->AddElementPoints())
			{
				HUD->AddElements(sf::Vector3i(entity_manager->game_entities[0]->GetAddFire(),
					entity_manager->game_entities[0]->GetAddWater(),
					entity_manager->game_entities[0]->GetAddWood()));
			}
			//Delete element points?
			else if(entity_manager->game_entities[0]->DeleteElementPoints())
			{
				HUD->DeleteElements(sf::Vector3i(entity_manager->game_entities[0]->GetDestroyFire(),
					entity_manager->game_entities[0]->GetDestroyWater(),
					entity_manager->game_entities[0]->GetDestroyWood()));
			}
		}

		//And here comes the player movement
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			m_window->close();
		};
		
			//kan inte gå över horisontlinjen:
			if (entity_manager->game_entities.at(0)->getPosition().y < 280){
				Vector2 vect (entity_manager->game_entities.at(0)->getPosition());
				vect.y = 280;
				entity_manager->game_entities.at(0)->setPosition(vect);
			};

			//kan inte gå ur vänster vägg:
			if (entity_manager->game_entities.at(0)->getPosition().x < 50){
				Vector2 vect (entity_manager->game_entities.at(0)->getPosition());
				vect.x = 50;
				entity_manager->game_entities.at(0)->setPosition(vect);
			};

			//kan inte gå under nedre kant:
			if (entity_manager->game_entities.at(0)->getPosition().y > 800/*playerheight*/){
				Vector2 vect (entity_manager->game_entities.at(0)->getPosition());
				vect.y = 1110-315/*playerheight*/;
				entity_manager->game_entities.at(0)->setPosition(vect);
			};

			//kan inte gå ur höger vägg:
			if (entity_manager->game_entities.at(0)->getPosition().x > 3619*2){
				Vector2 vect (entity_manager->game_entities.at(0)->getPosition());
				vect.x = 3619*2;
				entity_manager->game_entities.at(0)->setPosition(vect);
			}
			

		
		//Camera focus/movement:
		//kameran ska dock inte kunna visa vad som finns utanför banan åt höger(banans slut):
		//OBS MYCKET VIKTIGT MED > OCH = TILLSAMMANS
		if (camera.getPosition().x >= 3619*2){
			sf::Vector2f vect = camera.getPosition();
			vect.x = 3619*2;
			camera.setPosition(vect);
		}



		//hur långt inann kameran hänger med åt höger:
		else if (camera.getPosition().x < entity_manager->game_entities.at(0)->getPosition().x + 180){
			sf::Vector2f vect = camera.getPosition();
			vect.x = entity_manager->game_entities.at(0)->getPosition().x + 180;
			camera.setPosition(vect);

			//molnens position accelererar el saktas ner beroende åt vilket håll man går:
			cloud.moveX (0.055);
			cloud2.moveX (0.055);
			//cloud2.getPosition().x + 0.3;
			//background2 position:
			paralax1.moveX(0.07);
			paralax11.moveX(0.07);
			paralax2.moveX(0.1);
			paralax22.moveX(0.1);
			paralax3.moveX(-0.1);
			paralax33.moveX(-0.1);
		}
		
		//std::cout << camera.getPosition().x << " " << player.getPosition().x << std::endl;
		//kameran ska inte kunna visa vad som finns utanför banan åt vänster(banans början):
		if (camera.getPosition().x <= 512){
			sf::Vector2f vect = camera.getPosition();
			vect.x = 512;
			camera.setPosition(vect);
		}

		//hur långt innan kameran hänger med åt vänster
		else if (camera.getPosition().x > entity_manager->game_entities.at(0)->getPosition().x + 600){
			sf::Vector2f vect = camera.getPosition();
			vect.x = entity_manager->game_entities.at(0)->getPosition().x + 600;
			camera.setPosition(vect);

			//molnens position accelererar el saktas ner beroende åt vilket håll man går:
			cloud.moveX (-0.15);
			cloud2.moveX (-0.15);
			//cloud2.getPosition().x + 0.3;
			//background2 position:
			paralax1.moveX(-0.1);
			paralax11.moveX(-0.1);
			paralax2.moveX(-0.15);
			paralax22.moveX(-0.15);
			paralax3.moveX(+0.1);
			paralax33.moveX(+0.1);
			}
		
		
		//För att molnen ska spawna och despawna på rätt positioner:
		if(cloud.getPosition().x <= camera.getPosition().x - 4760){
			sf::Vector2f vect = cloud.getPosition();
			vect.x = camera.getPosition().x + 1920/2 + 1920;
			cloud.setPosition(vect);
		}
		if(cloud2.getPosition().x <= camera.getPosition().x - 4760){
			sf::Vector2f vect = cloud2.getPosition();
			vect.x = camera.getPosition().x + 1920/2 + 1920;
			cloud2.setPosition(vect);
		}

		cloud.moveX(-0.05);
		cloud2.moveX(-0.05);
	
		m_view.setCenter(camera.getPosition());
		m_window->setView(m_view);

		m_window->clear(sf::Color(0x40, 0x20, 0x30, 0xff));

		paralax2.draw(m_window);
		paralax22.draw(m_window);

		

		cloud.draw(m_window);
		cloud2.draw(m_window);
		
		paralax1.draw(m_window);
		paralax11.draw(m_window);


		
		//kommer fixa så att man kan köra delete på dom senare när dom är pekare så blir allt perfa:
		//spelplan1
		if (entity_manager->game_entities.at(0)->getPosition().x >= 0 && entity_manager->game_entities.at(0)->getPosition().x <= 4500){
				gameplayarea.draw(m_window);
				//std::cout << "Gra bakgrund framme" << std::endl;
			};
		
		//För att nästa spelplansdel inte ska spawna förrän man går dit:
		if (entity_manager->game_entities.at(0)->getPosition().x >= 1280 && entity_manager->game_entities.at(0)->getPosition().x <= 6400){
				gameplayarea2.draw(m_window);

				//std::cout << gameplayarea2.getPosition().x << std::endl;
			};
		
		
		
		HUD->Move((camera.getPosition().x-cameras_last_position.x), camera.getPosition().y - cameras_last_position.y);
		cameras_last_position = camera.getPosition();


		//Update portion
		if(!Pause)
		{
			entity_manager->Update(deltatime);
			HUD->Update(deltatime);
		}
		else
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				StartPauseTimer = true;
		}
		if(StartPauseTimer)
		{
			PauseTimer += deltatime;

			if(PauseTimer > 0.2)
			{
				StartPauseTimer = false;
				PauseTimer = 0.0f;
				Pause = false;
			}
		}
		

		//drawing portion of game loop
		draw_manager->Draw(m_window, entity_manager, HUD, draw_hitbox);
		
		//gräset som ska vara längst fram
		paralax3.draw(m_window);
		paralax33.draw(m_window);

		m_window->display();

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