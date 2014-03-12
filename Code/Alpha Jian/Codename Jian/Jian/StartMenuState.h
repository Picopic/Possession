//StartMenuState
//The StartMenu
//From the StartMenu you can enter three other states: "GameState"(Play Game), "HowToPlayState"(How to play) and "OptionsState"(Options).
//You will also be able to quit the game(Quit game), but that is not a state.

#pragma once
#include "stdafx.h"
#include "State.h"
#include "EntityManager.h"
#include "Spritemanager.h"

enum MenuOptions
{
	PLAY,
	HOWTOPLAY,
	OPTIONS,
	QUIT
};

class StartMenuState:public State{
public:
	StartMenuState(sf::RenderWindow* StartMenuWindow);
	~StartMenuState();
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
	MenuOptions current_option;
	bool options_changed;
	float options_changed_delay;

	//m_done är false tills man är klar med statet
	bool m_done;
	sf::RenderWindow* m_window;
	
	void UpdateDeltatime();
	sf::Clock game_clock;
	sf::Time previous_time;
	float deltatime;

	SpriteManager* sprite_manager;
	EntityManager *entity_manager;
};
