//WaveSystem.cpp

#include "stdafx.h"

//Forward declaring
#include "ObjectWave.h"
#include "EnemyWave.h"

#include "ConfigManager.h"
#include "EntityManager.h"

#include "WaveSystem.h"

//-----------------------Constructors and Destructors----------------------------------------//
WaveSystem::WaveSystem()
{
	m_fWidth = 0.0f;

	m_fPlayerX = 0.0f;

	m_ConfigManager = nullptr;

	m_iCurrentWave = 0;
}

WaveSystem::~WaveSystem()
{
	//Clear the Object waves
	for(int i = 0; i < m_ObjectWaves.size(); i++)
	{
		if(m_ObjectWaves[i] != nullptr)
		{
			delete m_ObjectWaves[i];
			m_ObjectWaves[i] = nullptr;
		}
	}

	//Clear the Enemy waves
	for(int i = 0; i < m_EnemyWaves.size(); i++)
	{
		if(m_EnemyWaves[i] != nullptr)
		{
			delete m_EnemyWaves[i];
			m_EnemyWaves[i] = nullptr;
		}
	}

	//Set the ConfigManager to null
	if(m_ConfigManager != nullptr)
		m_ConfigManager = nullptr;

	//Set the EntityManager to null
	if(m_EntityManager != nullptr)
		m_EntityManager = nullptr;
}
//----------------------End of Constructors and Destructors-----------------------------------//

//----------------------Essential Functions---------------------------------------------------//
bool WaveSystem::Initalise(ConfigManager* ConfigMgr, EntityManager* EntityMgr)
{
	//Initiate the ConfigManager and then validate it
	m_ConfigManager = ConfigMgr;
	if(m_ConfigManager == nullptr)
		return false;
	m_ConfigManager->ReadFile("WaveSystem.txt");

	//Initiate the EntityManager and then validate it
	m_EntityManager = EntityMgr;
	if(m_EntityManager == nullptr)
		return false;

	//Set the width of each wave segment
	m_fWidth = m_ConfigManager->ReadFloat("WaveWidth");

	//How many wavees?
	m_iNumberOfWaves = m_ConfigManager->ReadInt("NumberOfWaves");

	//Initalise the Objectwaves
	for(int i = 0; i < m_iNumberOfWaves; i++)
	{
		ObjectWave* TempObjectWave = new ObjectWave();
		if(TempObjectWave->Initalise(m_ConfigManager, m_EntityManager, i))
			m_ObjectWaves.push_back(TempObjectWave);
	}

	//Initalise the Enemywaves
	for(int i = 0; i < m_iNumberOfWaves; i++)
	{
		EnemyWave* TempEnemyWave = new EnemyWave();
		if(TempEnemyWave->Initalise(m_ConfigManager, m_EntityManager, i))
			m_EnemyWaves.push_back(TempEnemyWave);
	}

	return true;
}

void WaveSystem::Update(float PlayerDeltaX)
{
	m_fPlayerX += PlayerDeltaX;

	if(m_fPlayerX > m_fWidth)
	{
		int LastWave = m_iCurrentWave;
		m_iCurrentWave++;
		m_fPlayerX = 0.0f;
		ChangeWave(m_iCurrentWave, m_iCurrentWave - LastWave);
	}
		
	else if(m_fPlayerX < 0.0f)
	{
		int LastWave = m_iCurrentWave;
		m_iCurrentWave--;
		m_fPlayerX = m_fWidth;
		ChangeWave(m_iCurrentWave, m_iCurrentWave - LastWave);
	}
}

void WaveSystem::ChangeWave(int WaveNumber, int direction)
{
	//Set the object wave

	//Unactivate the wave that you went away from
	if(direction == 1 && (WaveNumber - 2) >= 0)
	{
		m_ObjectWaves[WaveNumber - 2]->UnActivate();
	}
	else if(direction == -1 && (WaveNumber + 2) < m_iNumberOfWaves)
	{
		m_ObjectWaves[WaveNumber + 2]->UnActivate();
	}

	//Activate the wave that you are heading to
	if(direction == 1 && (WaveNumber + 1) < m_iNumberOfWaves)
	{
		m_ObjectWaves[WaveNumber + 1]->Activate();
	}
	else if(direction == -1 && (WaveNumber - 1) >=0)
	{
		m_ObjectWaves[WaveNumber - 1]->Activate();
	}

	//If the enemy wave have not been spawned yet, spawn it
}

//----------------------End of Essential Functions-------------------------------------------//

//----------------------Access Functions-----------------------------------------------------//

//----------------------End of Access Functions----------------------------------------------//