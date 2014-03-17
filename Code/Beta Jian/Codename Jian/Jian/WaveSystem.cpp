//WaveSystem.cpp

#include "stdafx.h"

//Forward declaring
#include "ObjectWave.h"

#include "ConfigManager.h"

#include "WaveSystem.h"

//-----------------------Constructors and Destructors----------------------------------------//
WaveSystem::WaveSystem()
{
	m_ConfigManager = nullptr;
}

WaveSystem::~WaveSystem()
{
	//Clear the Object waves
	for(int i = 0; i < ObjectWaves.size(); i++)
	{
		if(ObjectWaves[i] != nullptr)
		{
			delete ObjectWaves[i];
			ObjectWaves[i] = nullptr;
		}
	}
}

//----------------------Essential Functions---------------------------------------------------//
bool WaveSystem::Initalise(ConfigManager* ConfigMgr)
{
	m_ConfigManager = ConfigMgr;
	if(m_ConfigManager == nullptr)
		return false;
	m_ConfigManager->ReadFile("WaveSystem.txt");
}