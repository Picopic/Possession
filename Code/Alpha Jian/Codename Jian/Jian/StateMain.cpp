//main.cpp

#include "stdafx.h"

#include "StateManager.h"
#include "State.h"
#include "StartMenuState.h"
#include "OptionsState.h"
#include "GameState.h"
#include "HowToPlayState.h"

using namespace sf;

int main()
{
	sf::RenderWindow* m_window;
	m_window = new sf::RenderWindow(VideoMode(1024,640), "States");
	StateManager st_mgr;
	st_mgr.Attach(new GameState(m_window));
	st_mgr.Attach(new StartMenuState(m_window));
	st_mgr.Attach(new OptionsState(m_window));
	st_mgr.Attach(new HowToPlayState(m_window));

	st_mgr.Initialize();

	st_mgr.SetState("StartMenuState");
	while (true){
		Event event;
		while(m_window->pollEvent(event)) {
			if(event.type == Event::Closed) {
				m_window->close();
			};
			if(Keyboard::isKeyPressed(Keyboard::Escape)) {
			m_window->close();
			return 0;
			}
		};
		st_mgr.Update();
		//m_window->clear(Color(0x99, 0x20, 0x55, 0xff));
		st_mgr.Draw();
		//m_window->display();
	}
	return 0;
}
