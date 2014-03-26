//GoodWinState.cpp
//Enter this state from the StartMenuState.
//You can only go back to StartMenuState from here.

#include "stdafx.h"
#include "GoodWinState.h"

using namespace sf;

GoodWinState::GoodWinState(sf::RenderWindow* GoodwinWindow){

	goodwintexture.loadFromFile("../data/f/GoodWin.png");
	
	goodwinsprite.setTexture(goodwintexture);
	//goodwinsprite.setOrigin(m_slider.getLocalBounds().width/2, m_slider.getLocalBounds().height/2);
	goodwinsprite.setPosition(0,0);

	m_window = GoodwinWindow;
}

GoodWinState::~GoodWinState(){

}

bool GoodWinState::Initialize(){
	m_done = false;
	return false;
}

bool GoodWinState::Enter(){
	
	std::cout << "Welcome to the GoodWinState" << std::endl;

	return false;
}

bool GoodWinState::Exit(){
	return false;
}

bool GoodWinState::Update(){

	m_done = false;

	if(Keyboard::isKeyPressed(Keyboard::Space)) {
		m_next_state = "StartMenuState";
		m_done=true;
		
	};
	return m_done;
}

std::string GoodWinState::Next(){
	return m_next_state;
}

bool GoodWinState::IsType(const std::string& Type){
	return Type == "GoodWinState";
}

bool GoodWinState::Draw(){
	
	m_window->draw(goodwinsprite);
	
	m_window->clear(Color(0x99, 0x55, 0x99, 0xff));
	m_window->display();
	return false;
}