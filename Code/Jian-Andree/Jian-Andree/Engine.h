//Engine.h

#pragma once

#include "DrawManager.h"
#include "EntityManager.h"


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

private:
	sf::RenderWindow window;
	sf::ContextSettings window_settings;
	int window_width;
	int window_height;
	int window_anti_aliasing;
};