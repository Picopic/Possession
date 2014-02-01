//Engine.h

#pragma once

#include "DrawManager.h"
#include "EntityManager.h"
#include "Input.h"


class Engine
{
public:
	Engine();
	~Engine();
	
	bool Init();
	void Run();
	void Cleanup();

	DrawManager *draw_manager;
	EntityManager *entity_manager;
	Keyboard keyboard;

private:
	void UpdateDeltatime();

	sf::RenderWindow window;
	sf::ContextSettings window_settings;
	sf::Clock game_clock;
	sf::Time previous_time;
	float deltatime;
	int window_width;
	int window_height;
	int window_anti_aliasing;
};