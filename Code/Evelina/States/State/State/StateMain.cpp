//main.cpp

#include "stdafx.h"

#include "StateManager.h"
#include "State.h"
#include "StartMenuState.h"
#include "OptionsState.h"
#include "GameState.h"
#include "HowToPlayState.h"


int main()
{
	sf::RenderWindow* m_window;
	m_window = new sf::RenderWindow();
	StateManager st_mgr;
	st_mgr.Attach(new GameState);
	st_mgr.Attach(new StartMenuState);
	st_mgr.Attach(new OptionsState);
	st_mgr.Attach(new HowToPlayState);

	st_mgr.Initialize();

	st_mgr.SetState("StartMenuState");
	while (true){
		st_mgr.Update();
	}
	//
	//Kan man göra så att esc fungerar här? Alltså så att man kan stänga ner programmet med ESC oavsett vars man är om jag lägger in det här?
	//	if(Keyboard::isKeyPressed(Keyboard::Escape)) {
	//		window.close();
	//};
}