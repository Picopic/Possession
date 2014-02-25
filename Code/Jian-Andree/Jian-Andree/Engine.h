//Engine.h

#pragma once

#include "DrawManager.h"
#include "EntityManager.h"
#include "Spritemanager.h"
#include "AnimationManager.h"
#include "HeadsUpDisplay.h"
#include "SoundManager.h"
#include "Enums.h"


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
	SpriteManager *sprite_manager;
	SoundManager *sound_manager;
	HeadsUpDisplay *HUD;

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

	sf::Music background_music;
};