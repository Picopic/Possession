//DeadState.h
//You can only go back to StartMenuState from here.

#pragma once
#include "stdafx.h"
#include "State.h"

class DeadState:public State{
public:
	DeadState(sf::RenderWindow* DeadState);
	~DeadState();
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

	sf::Texture deadtexture;
	sf::Sprite deadsprite;

	//m_done är false tills man är klar med statet
	bool m_done;
	sf::RenderWindow* m_window;
};