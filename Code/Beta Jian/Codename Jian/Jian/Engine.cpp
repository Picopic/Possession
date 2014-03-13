//Engine.cpp
#include "stdafx.h"
#include "Engine.h"

Engine::Engine()
{
	window_width = 1920;
	window_height = 1080;
	window_anti_aliasing = 4;
}

Engine::~Engine()
{

}

bool Engine::Init()
{
	window_settings.antialiasingLevel = window_anti_aliasing;
	window=new sf::RenderWindow(sf::VideoMode(window_width, window_height, sf::Style::Fullscreen), "Jian", sf::Style::Default, window_settings);

	draw_manager = new DrawManager;
	
	sound_manager = new SoundManager;
	sound_manager->Initialise("../data/Sound/");

	sprite_manager = new SpriteManager;
	sprite_manager->Initialise("../data/Spritesheets2/");

	HUD = new HeadsUpDisplay;
	if(!HUD->Initialise(sprite_manager))
	{
		return false;
	}
	
	entity_manager = new EntityManager(sprite_manager, sound_manager);

	previous_time = game_clock.restart();

	deltatime = 0.01f;

	return true;
}

void Engine::Run()
{
	//gameloop
	while(window->isOpen())
	{
		//event handling
		sf::Event event;
		while(window->pollEvent(event))
		{
			switch(event.type)
			{
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::KeyPressed:
				if(event.key.code == sf::Keyboard::Escape)
				{
					window->close();
				}
				break;
			}
		}

		//deltatime
		UpdateDeltatime();

		//game logic

		entity_manager->Update(deltatime);

		//drawing portion of game loop
		draw_manager->Draw(window, entity_manager, HUD, false);

		//std::cout << entity_manager->game_entities.size() << std::endl;
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
		delete entity_manager;
		entity_manager = nullptr;
	}
	if(sprite_manager != nullptr)
	{
		delete sprite_manager;
		sprite_manager = nullptr;
	}
}

void Engine::UpdateDeltatime()
{
	sf::Time temp_time;
	temp_time = game_clock.getElapsedTime();
	deltatime = (temp_time.asSeconds() - previous_time.asSeconds());
	previous_time = temp_time;
}