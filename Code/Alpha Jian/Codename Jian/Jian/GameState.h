//GameState.h
//Where you play the game. Enter this state from the StartMenuState.

#pragma once
#include "stdafx.h"
#include "State.h"
#include "Camera.h"
#include "Cloud.h"
#include "Gameplayarea.h"
#include "Paralax.h"
#include "Paralax2.h"
#include "DrawManager.h"
#include "SpriteManager.h"
#include "EntityManager.h"
#include "HeadsUpDisplay.h"
#include "SoundManager.h"
#include "ConfigManager.h"
#include "Paralax3.h"

#include "EnemyWaves.h"

class GameState:public State{
public:
	GameState(sf::RenderWindow* StartMenuWindow);
	~GameState();
	bool Initialize();
	bool Enter();
	bool Exit();
	bool Update();

	//Dessa är de som Jerry tipsade om, nedan kommer ytterligare några
	//String hanterar text, IsType returns true if type equals current state
	std::string Next();
	bool IsType(const std::string& Type);
	//Cleanup är valfri, går även att köra i dekonstruktorn
	//virtual void Cleanup()=0;
	//Draw går att ha i Update, men blir snyggare som egen. Allt som visas på skärmen har man i Draw.
	bool Draw();



private:
	std::string m_next_state;

	void UpdateDeltatime();

	//m_done är false tills man är klar med statet
	bool m_done;
	sf::RenderWindow* m_window;
	sf::View m_view;

	sf::Clock game_clock;
	sf::Time previous_time;
	float deltatime;

	sf::Vector2f cameras_last_position;
	Camera camera;
	Cloud cloud;
	Cloud cloud2;
	Gameplayarea gameplayarea;
	Gameplayarea gameplayarea2;
	Paralax paralax1;
	Paralax paralax11;
	Paralax2 paralax2;
	Paralax2 paralax22;
	Paralax3 paralax3;
	Paralax3 paralax33;

	DrawManager *draw_manager;
	SpriteManager *sprite_manager;
	EntityManager *entity_manager;
	HeadsUpDisplay *HUD;
	SoundManager *sound_manager;
	ConfigManager *config_manager;
	sf::Music background_music;

	EnemyWaves* enemy_waves;

	bool draw_hitbox;
};