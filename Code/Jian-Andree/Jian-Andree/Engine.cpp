//Engine.cpp
#include "stdafx.h"
#include "Engine.h"

Engine::Engine()
{
	window_width = 1280;
	window_height = 720;
	window_anti_aliasing = 4;
}

Engine::~Engine()
{

}

bool Engine::Init()
{
	window_settings.antialiasingLevel = window_anti_aliasing;
	window.create(sf::VideoMode(window_width, window_height), "Jian", sf::Style::Default, window_settings);

	sound_manager = new SoundManager;
	sound_manager->Initialise("../data/Sound/");
	

	draw_manager = new DrawManager;
	
	sprite_manager = new SpriteManager;
	sprite_manager->Initialise("../data/Spritesheets/");
	
	entity_manager = new EntityManager(sprite_manager, sound_manager);

	HUD = new HeadsUpDisplay;
	if(!HUD->Initialise(sprite_manager))
	{
		return false;
	}

	previous_time = game_clock.restart();

	deltatime = 0.01f;
	
	//music
	if(!background_music.openFromFile("../data/Sound/wizhit.wav"))
	{
		return false;
	}

	return true;
}

void Engine::Run()
{
	//background_music.play();
	//background_music.setLoop(true);

	entity_manager->Init();
	entity_manager->AttachEntity(PLAYER, Vector2(0, 300), 50, 110, FIRE);
	entity_manager->AttachEntity(FIREFOE, Vector2(600, 0), 100, 80, FIRE);

	//gameloop
	while(window.isOpen())
	{
		//event handling
		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if(event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				break;
			}
		}

		//deltatime
		UpdateDeltatime();

		//game logic
		entity_manager->Update(deltatime);

		//drawing portion of game loop
		draw_manager->Draw(&window, entity_manager, HUD);

	}
}

void Engine::Cleanup()
{
	if(draw_manager != nullptr)
	{
		delete draw_manager;
		draw_manager = nullptr;
	}
	if(entity_manager != nullptr)
	{
		entity_manager->Cleanup();
		delete entity_manager;
		entity_manager = nullptr;
	}
	if(sprite_manager != nullptr)
	{
		sprite_manager->Cleanup();
		delete sprite_manager;
		sprite_manager = nullptr;
	}
	if(HUD != nullptr)
	{
		HUD->Cleanup();
		delete HUD;
		HUD = nullptr;
	}

	if(sound_manager != nullptr)
	{
		sound_manager->Cleanup();
		delete sound_manager;
		sound_manager = nullptr;
	}
}

void Engine::UpdateDeltatime()
{
	sf::Time temp_time;
	temp_time = game_clock.getElapsedTime();
	deltatime = (temp_time.asSeconds() - previous_time.asSeconds());
	previous_time = temp_time;
}