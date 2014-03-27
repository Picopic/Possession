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

	GameplayAreaWidth = 3650;
	CurrentArea = 0;
	PreviousPlayerX = 0.0f;
	PlayerWalkDistance = 0.0f;

	draw_manager = nullptr;
	sprite_manager = nullptr;
	entity_manager = nullptr;
	HUD = nullptr;
	sound_manager = nullptr;
	config_manager = nullptr;
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

	for(int i = 0; i < Gameplayareas.size(); i++)
	{
		if(Gameplayareas[i] != nullptr)
		{
			delete Gameplayareas[i];
			Gameplayareas[i] = nullptr;
		}
	}
}

bool GameState::Initialize(){

	PauseTimer = 0.0f;


	//View port
	camera.setPosition(sf::Vector2f(1920/2, 1080/2));
	cameras_last_position = camera.getPosition();

	m_view.setCenter(camera.getPosition());
	m_view.setSize(sf::Vector2f(1920,1080));

	//----------------------

	if(draw_manager == nullptr)
		draw_manager = new DrawManager;

	if(sound_manager == nullptr)
	{
		sound_manager = new SoundManager;
		sound_manager->Initialise("../data/Sound/");
	}

	if(sprite_manager == nullptr)
	{
		sprite_manager = new SpriteManager;
		sprite_manager->Initialise("../data/Spritesheets2/");

		//Precache the resources
		sprite_manager->LoadTexture("MC SPRITESHEET 252p w transparency.png");
		sprite_manager->LoadTexture("WATER SPRITESHEET 315p.png");
		sprite_manager->LoadTexture("FIRE SPRITESHEET 315p.png");
		sprite_manager->LoadTexture("WOOD SPRITESHEET 495x405p.png");
		sprite_manager->LoadTexture("Projectile Spritesheet Small.png");
		sprite_manager->LoadTexture("Lost Souls Spritesheet.png");

		LoadLevel();
		LoadParallax();
	}

	if(HUD == nullptr)
	{
		HUD = new HeadsUpDisplay;
		if(!HUD->Initialise(sprite_manager))
		{
			return false;
		}
	}

	if(entity_manager == nullptr)
	{
		entity_manager = new EntityManager(sprite_manager, sound_manager);

		if(config_manager == nullptr)
		{
			config_manager = new ConfigManager;
			config_manager->Initialise("../data/Configs/");
			config_manager->ReadFile("Config.txt");
			config_manager->ReadFile("Enemywaves.txt");
			config_manager->ReadFile("WaveSystem.txt");
		}

		if(enemy_waves == nullptr)
			enemy_waves = new EnemyWaves(entity_manager, config_manager);

		entity_manager->Init(enemy_waves);
	}

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
	//Create player
	entity_manager->CreatePlayer();
	HUD->Restart();
	enemy_waves->Restart();

	entity_manager->AttachStaticObject(config_manager, "HITBOXTREE");
	entity_manager->AttachStaticObject(config_manager, "HITBOXHANGEDBODY");

	std::cout << "Welcome to the GameState" << std::endl;
	std::cout << "Press 4 to go back to StartMenuState" <<std::endl;

	UpdateDeltatime();

	return false;
}

bool GameState::Exit(){
	entity_manager->ClearGameEntities();

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
	HUDUpdate();

	//player movement
	PlayerMovement();

	//Camera movement
	CameraMovement();

	//Parallax movement
	UpdateParallax();

	//Update the movement
	UpdateGameplayArea();
	

	m_view.setCenter(camera.getPosition());
	m_window->setView(m_view);

	m_window->clear(sf::Color(entity_manager->game_entities.at(0)->getRed(), entity_manager->game_entities.at(0)->getGreen(), entity_manager->game_entities.at(0)->getBlue(), 255));

	//Draw the parallax
	DrawParallax();

	//Draw the gameplay areas
	DrawGameplayAreas();

	//move the HUD
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

	if(entity_manager->SwitchState())
	{
		m_next_state = "StartMenuState";
		m_done = true;
	}
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

	if(deltatime > 0.1)
		deltatime = 0.1f;
}


//-------------------------------ANDRÉS FUNCTIONS----------------------------//

bool GameState::LoadLevel()
{
	//Initalise all the gameplay areas


	//initalise the parallax
	LoadParallax();

	//Initalise the gameplay areas
	int GameplayNumber = 0;

	Gameplayareas.push_back(new Gameplayarea());
	Gameplayareas[GameplayNumber]->initialize("Part 1 - Tree.png", sprite_manager);
	Gameplayareas[GameplayNumber]->setPosition(sf::Vector2f(GameplayNumber*GameplayAreaWidth, 0));
	GameplayNumber++;

	Gameplayareas.push_back(new Gameplayarea());
	Gameplayareas[GameplayNumber]->initialize("Part 2 - Forest 1.png", sprite_manager);
	Gameplayareas[GameplayNumber]->setPosition(sf::Vector2f(GameplayNumber*GameplayAreaWidth, 0));
	GameplayNumber++;

	Gameplayareas.push_back(new Gameplayarea());
	Gameplayareas[GameplayNumber]->initialize("Part 3 - Forest 2.png", sprite_manager);
	Gameplayareas[GameplayNumber]->setPosition(sf::Vector2f(GameplayNumber*GameplayAreaWidth, 0));
	GameplayNumber++;

	Gameplayareas.push_back(new Gameplayarea());
	Gameplayareas[GameplayNumber]->initialize("Part 4 - Village 1.png", sprite_manager);
	Gameplayareas[GameplayNumber]->setPosition(sf::Vector2f(GameplayNumber*GameplayAreaWidth, 0));
	GameplayNumber++;

	Gameplayareas.push_back(new Gameplayarea());
	Gameplayareas[GameplayNumber]->initialize("Part 5 - Village 2.png", sprite_manager);
	Gameplayareas[GameplayNumber]->setPosition(sf::Vector2f(GameplayNumber*GameplayAreaWidth, 0));
	GameplayNumber++;

	Gameplayareas.push_back(new Gameplayarea());
	Gameplayareas[GameplayNumber]->initialize("Part 6 - Gunillas place.png", sprite_manager);
	Gameplayareas[GameplayNumber]->setPosition(sf::Vector2f(GameplayNumber*GameplayAreaWidth, 0));
	GameplayNumber++;

	//ljust och mörkt på himlen
	gradienthimmel.setPosition(sf::Vector2f(camera.getPosition().x, camera.getPosition().y));
	gradienthimmel.initialize();

	return true;
}

bool GameState::LoadParallax()
{
	//Moln
	cloud.setPosition(sf::Vector2f(0, 0));
	cloud.initialize();

	cloud2.setPosition(sf::Vector2f(3840,0));
	cloud2.initialize();

	//främre berg
	paralax1.setPosition(sf::Vector2f(-150, -15+90));
	paralax1.initialize();
	paralax11.setPosition(sf::Vector2f(3850, -15+90));
	paralax11.initialize();

	//bakre berg
	paralax2.setPosition(sf::Vector2f(-150, +50+70));
	paralax2.initialize();
	paralax22.setPosition(sf::Vector2f(3354, +50+70));
	paralax22.initialize();

	//gräsparallax
	paralax3.setPosition(sf::Vector2f(-50, +1080-65));
	paralax3.initialize();
	paralax33.setPosition(sf::Vector2f(+3150, +1080-65));
	paralax33.initialize();

	//måne
	moon.setPosition(sf::Vector2f(camera.getPosition().x+670, camera.getPosition().y-560));
	moon.initialize();

	return true;
}

void GameState::UpdateParallax()
{
	//För att molnen ska spawna och despawna på rätt positioner:
	if(cloud.getPosition().x < camera.getPosition().x - 3840 - (1920/2)){
		cloud.setPosition(sf::Vector2f(cloud2.getPosition().x + 3840, 0));
	}
	if(cloud.getPosition().x > camera.getPosition().x - (1920/2) + 3840){
		cloud.setPosition(sf::Vector2f(cloud2.getPosition().x - 3840, 0));	
	}

	if(cloud2.getPosition().x < camera.getPosition().x - 3840 - (1920/2)){
		cloud2.setPosition(sf::Vector2f(cloud.getPosition().x + 3840, 0));
	}
	if(cloud2.getPosition().x > camera.getPosition().x - (1920/2) + 3840){
		cloud2.setPosition(sf::Vector2f(cloud.getPosition().x - 3840, 0));
	}

	 //parallax1 främre berg spawn och despawn:
	if(paralax1.getPosition().x < camera.getPosition().x - 4000 - (1920/2)){
		paralax1.setPosition(sf::Vector2f(paralax11.getPosition().x + 4000, -15+90));
	}
	if(paralax1.getPosition().x > camera.getPosition().x - (1920/2) + 4000){
		paralax1.setPosition(sf::Vector2f(paralax11.getPosition().x - 4000, -15+90));	
	}


	if(paralax11.getPosition().x < camera.getPosition().x - 4000 - (1920/2)){
		paralax11.setPosition(sf::Vector2f(paralax1.getPosition().x + 4000, -15+90));
	}
	if(paralax11.getPosition().x > camera.getPosition().x - (1920/2) + 4000){
		paralax11.setPosition(sf::Vector2f(paralax1.getPosition().x - 4000, -15+90));
	}

	 //parallax2 bakre berg spawn och despawn:
	if(paralax2.getPosition().x < camera.getPosition().x - 3354 - (1920/2)){
		paralax2.setPosition(sf::Vector2f(paralax22.getPosition().x + 3354, +50+70));
	}
	if(paralax2.getPosition().x > camera.getPosition().x - (1920/2) + 3354){
		paralax2.setPosition(sf::Vector2f(paralax22.getPosition().x - 3354, +50+70));	
	}


	if(paralax22.getPosition().x < camera.getPosition().x - 3354 - (1920/2)){
		paralax22.setPosition(sf::Vector2f(paralax2.getPosition().x + 3354, +50+70));
	}
	if(paralax22.getPosition().x > camera.getPosition().x - (1920/2) + 3354){
		paralax22.setPosition(sf::Vector2f(paralax2.getPosition().x - 3354, +50+70));
	}

	 //parallax3 gräs:
	if(paralax3.getPosition().x < camera.getPosition().x - 3250 - (1920/2)){
		paralax3.setPosition(sf::Vector2f(paralax33.getPosition().x + 3250, +1080-65));
	}
	if(paralax3.getPosition().x > camera.getPosition().x - (1920/2) + 3250){
		paralax3.setPosition(sf::Vector2f(paralax33.getPosition().x - 3250, +1080-65));	
	}


	if(paralax33.getPosition().x < camera.getPosition().x - 3250 - (1920/2)){
		paralax33.setPosition(sf::Vector2f(paralax3.getPosition().x + 3250, +1080-65));
	}
	if(paralax33.getPosition().x > camera.getPosition().x - (1920/2) + 3250){
		paralax33.setPosition(sf::Vector2f(paralax3.getPosition().x - 3250, +1080-65));
	}




	cloud.moveX(-0.05);
	cloud2.moveX(-0.05);

	gradienthimmel.setPosition(sf::Vector2f(camera.getPosition().x, camera.getPosition().y));
}

void GameState::CameraMovement()
{
	//Camera focus/movement:
	//kameran ska dock inte kunna visa vad som finns utanför banan åt höger(banans slut):
	//OBS MYCKET VIKTIGT MED > OCH = TILLSAMMANS
	if (camera.getPosition().x >= GameplayAreaWidth*Gameplayareas.size() - 1400){
		sf::Vector2f vect = camera.getPosition();
		vect.x = GameplayAreaWidth*Gameplayareas.size() - 1400;
		camera.setPosition(vect);
	}


	//hur långt inann kameran hänger med åt höger:
	else if (camera.getPosition().x < entity_manager->game_entities.at(0)->getPosition().x + 180){
		sf::Vector2f vect = camera.getPosition();
		vect.x = entity_manager->game_entities.at(0)->getPosition().x + 180;
		camera.setPosition(vect);

		//molnens position accelererar el saktas ner beroende åt vilket håll man går:
		cloud.moveX (entity_manager->game_entities.at(0)->getSpeed()*deltatime-0.5);
		cloud2.moveX (entity_manager->game_entities.at(0)->getSpeed()*deltatime-0.5);
		//cloud2.getPosition().x + 0.3;
		//background2 position:
		paralax1.moveX((entity_manager->game_entities.at(0)->getSpeed()*deltatime-0.5)/2);
		paralax11.moveX((entity_manager->game_entities.at(0)->getSpeed()*deltatime-0.5)/2);
		paralax2.moveX(entity_manager->game_entities.at(0)->getSpeed()*deltatime-0.5);
		paralax22.moveX(entity_manager->game_entities.at(0)->getSpeed()*deltatime-0.5);
		paralax3.moveX(-0.3);
		paralax33.moveX(-0.3);
		moon.moveX(entity_manager->game_entities.at(0)->getSpeed()*deltatime);
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
		cloud.moveX (-entity_manager->game_entities.at(0)->getSpeed()*deltatime+0.5);
		cloud2.moveX (-entity_manager->game_entities.at(0)->getSpeed()*deltatime+0.5);
		//cloud2.getPosition().x + 0.3;
		//background2 position:
		paralax1.moveX((-entity_manager->game_entities.at(0)->getSpeed()*deltatime+0.5)/2);
		paralax11.moveX((-entity_manager->game_entities.at(0)->getSpeed()*deltatime+0.5)/2);
		paralax2.moveX(-entity_manager->game_entities.at(0)->getSpeed()*deltatime+0.5);
		paralax22.moveX(-entity_manager->game_entities.at(0)->getSpeed()*deltatime+0.5);
		paralax3.moveX(+0.3);
		paralax33.moveX(+0.3);
		moon.moveX(-entity_manager->game_entities.at(0)->getSpeed()*deltatime);
	}
}

void GameState::PlayerMovement()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		m_window->close();
	};

	//kan inte gå över horisontlinjen:
	if (entity_manager->game_entities.at(0)->getPosition().y < 320){
		Vector2 vect (entity_manager->game_entities.at(0)->getPosition());
		vect.y = 320;
		entity_manager->game_entities.at(0)->setPosition(vect);
	};

	//kan inte gå ur vänster vägg:
	if (entity_manager->game_entities.at(0)->getPosition().x < 600){
		Vector2 vect (entity_manager->game_entities.at(0)->getPosition());
		vect.x = 600;
		entity_manager->game_entities.at(0)->setPosition(vect);
	};

	//kan inte gå under nedre kant:
	if (entity_manager->game_entities.at(0)->getPosition().y > 800/*playerheight*/){
		Vector2 vect (entity_manager->game_entities.at(0)->getPosition());
		vect.y = 1110-315/*playerheight*/;
		entity_manager->game_entities.at(0)->setPosition(vect);
	};

	//kan inte gå ur höger vägg:
	if (entity_manager->game_entities.at(0)->getPosition().x > GameplayAreaWidth*Gameplayareas.size() - 600){
		Vector2 vect (entity_manager->game_entities.at(0)->getPosition());
		vect.x = GameplayAreaWidth* Gameplayareas.size() - 600;
		entity_manager->game_entities.at(0)->setPosition(vect);
	}
}

void GameState::HUDUpdate()
{
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
}

void GameState::DrawParallax()
{
	gradienthimmel.draw(m_window);

	moon.draw(m_window);

	paralax2.draw(m_window);
	paralax22.draw(m_window);

	cloud.draw(m_window);
	cloud2.draw(m_window);

	paralax1.draw(m_window);
	paralax11.draw(m_window);
}

void GameState::DrawGameplayAreas()
{
	if(CurrentArea > 1)
		Gameplayareas[CurrentArea - 2]->draw(m_window);

	if(CurrentArea > 0)
		Gameplayareas[CurrentArea - 1]->draw(m_window);

	Gameplayareas[CurrentArea]->draw(m_window);
	if(CurrentArea < (Gameplayareas.size() - 1))
		Gameplayareas[CurrentArea + 1]->draw(m_window);
}

void GameState::UpdateGameplayArea()
{
	PlayerWalkDistance += entity_manager->game_entities[0]->getPosition().x - PreviousPlayerX;
	PreviousPlayerX = entity_manager->game_entities[0]->getPosition().x;

	if(PlayerWalkDistance > GameplayAreaWidth)
	{
		CurrentArea++;
		PlayerWalkDistance = 0.0f;
	}
	if(PlayerWalkDistance < -GameplayAreaWidth)
	{
		CurrentArea--;
		PlayerWalkDistance = 0.0f;
	}
}