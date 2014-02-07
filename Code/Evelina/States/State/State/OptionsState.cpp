//OptionsState.cpp
//You can choose to enter "Options" from the StartMenuState.
//You can only go back to StartMenuState from here.

#include "stdafx.h"
#include "OptionsState.h"

OptionsState::OptionsState(){

}

OptionsState::~OptionsState(){

}

bool OptionsState::Initialize(){
	m_done = false;
	return false;
}

bool OptionsState::Enter(){
	return false;
}

bool OptionsState::Exit(){
	return false;
}

bool OptionsState::Update(){
	std::cout << "OptionsState" << std::endl;
	m_done = true;
	m_next_state = "HowToPlayState";
	return m_done;
}

std::string OptionsState::Next(){
	return m_next_state;
}

bool OptionsState::IsType(const std::string& Type){
	return Type == "OptionsState";
}

bool OptionsState::Draw(){
	return false;
}
