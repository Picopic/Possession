//GameState.h
//Where you play the game. Enter this state from the StartMenuState.

#pragma once
#include "stdafx.h"
#include "State.h"
#include "Camera.h"
#include "Cloud.h"
#include "Gameplayarea.h"
#include "Paralax.h"
#include "Player.h"
#include "DrawManager.h"
#include "SpriteManager.h"
#include "EntityManager.h"
#include "HeadsUpDisplay.h"

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



private:
	std::string m_next_state;

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
	Paralax paralax;
	//Player player;

	DrawManager *draw_manager;
	SpriteManager *sprite_manager;
	EntityManager *entity_manager;
	HeadsUpDisplay *HUD;
};