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
#include "Moon.h"
#include "Gradienthimmel.h"

#include "EnemyWaves.h"

class GameState:public State{
public:
	GameState(sf::RenderWindow* StartMenuWindow);
	~GameState();
	bool Initialize();
	bool Enter();
	bool Exit();
	bool Update();

	//Dessa �r de som Jerry tipsade om, nedan kommer ytterligare n�gra
	//String hanterar text, IsType returns true if type equals current state
	std::string Next();
	bool IsType(const std::string& Type);
	//Cleanup �r valfri, g�r �ven att k�ra i dekonstruktorn
	//virtual void Cleanup()=0;
	//Draw g�r att ha i Update, men blir snyggare som egen. Allt som visas p� sk�rmen har man i Draw.
	bool Draw();

	bool LoadLevel();

private:
	std::string m_next_state;

	//Andr�s funktioner
	bool LoadParallax();
	void UpdateParallax();
	void UpdateGameplayArea();

	void CameraMovement();
	void PlayerMovement();

	void HUDUpdate();

	void DrawParallax();
	void DrawGameplayAreas();
	//slut p� Andr�s funktioner

	void UpdateDeltatime();

	//m_done �r false tills man �r klar med statet
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
	Moon moon;
	Gradienthimmel gradienthimmel;

	DrawManager *draw_manager;
	SpriteManager *sprite_manager;
	EntityManager *entity_manager;
	HeadsUpDisplay *HUD;
	SoundManager *sound_manager;
	ConfigManager *config_manager;
	sf::Music background_music;

	EnemyWaves* enemy_waves;
	
	bool Pause;
	bool StartPauseTimer;
	float PauseTimer;

	//Gameplay areas
	std::vector<Gameplayarea*> Gameplayareas;
	float GameplayAreaWidth;
	int CurrentArea;
	float PreviousPlayerX, PlayerWalkDistance;
};