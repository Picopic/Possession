//GameState.h
//Where you play the game. Enter this state from the StartMenuState.

#pragma once
#include "stdafx.h"
#include "State.h"

class GameState:public State{
public:
	GameState();
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

	//m_done �r false tills man �r klar med statet
	bool m_done;
};