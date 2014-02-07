//HowToPlayState.cpp
//Enter this state from the StartMenuState.
//You can only go back to StartMenuState from here.

#include "HowToPlayState.h"

HowToPlayState::HowToPlayState(){

}

HowToPlayState::~HowToPlayState(){

}

bool HowToPlayState::Initialize(){
	m_done = false;
	return false;
}

bool HowToPlayState::Enter(){
	return false;
}

bool HowToPlayState::Exit(){
	return false;
}

bool HowToPlayState::Update(){
	std::cout << "HowToPlay." << std::endl;
	m_done = true;
	//m_next_state = "OptionsState";
	return m_done;
}

std::string HowToPlayState::Next(){
	return m_next_state;
}

bool HowToPlayState::IsType(const std::string& Type){
	return Type == "HowToPlayState";
}

bool HowToPlayState::Draw(){
	return false;
}