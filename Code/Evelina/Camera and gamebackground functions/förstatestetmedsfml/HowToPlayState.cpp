//HowToPlayState.cpp
//Enter this state from the StartMenuState.
//You can only go back to StartMenuState from here.

#include "stdafx.h"

#include <string>

#include "HowToPlayState.h"

using namespace sf;

HowToPlayState::HowToPlayState(){

}

HowToPlayState::~HowToPlayState(){

}

bool HowToPlayState::Initialize(){
	m_done = false;
	return false;
}

bool HowToPlayState::Enter(){
	std::cout << " " << std::endl;
	std::cout << "Welcome to HowToPlayState" << std::endl;
	std::cout << "Press 5 to go back to StartMenuState" << std::endl;
	return false;
}

bool HowToPlayState::Exit(){
	return false;
}

bool HowToPlayState::Update(){
	m_done=false;

	if(Keyboard::isKeyPressed(Keyboard::Num5)){
		m_done=true;
		m_next_state= "StartMenuState";
		return m_done;
	}
};


std::string HowToPlayState::Next(){
	return m_next_state;
}

bool HowToPlayState::IsType(const std::string& Type){
	return Type == "HowToPlayState";
}

bool HowToPlayState::Draw(){
	return false;
}