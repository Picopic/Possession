//Enemywave.cpp

#include "stdafx.h"

//Forward declarations of classes
#include "Entity.h"
#include "ConfigManager.h"
#include "EntityManager.h"

#include "EnemyWave.h"

//-----------------------Constructors and Destructors----------------------------------------//
EnemyWave::EnemyWave()
{
	m_ConfigManager = nullptr;
	m_EntityManager = nullptr;
	m_bSpawned = false;
}

EnemyWave::~EnemyWave()
{
	//set the EntityManager to null
	if(m_EntityManager != nullptr)
		m_EntityManager = nullptr;

	//Set the ConfigManager to null
	if(m_ConfigManager != nullptr)
		m_ConfigManager = nullptr;

	//Clear the vector of entities
	for(int i = 0; i < WaveEnemies.size(); i++)
	{
		if(WaveEnemies[i] != nullptr)
			WaveEnemies[i] = nullptr;
	}
}
//----------------------End of Constructors and Destructors-----------------------------------//

//----------------------Essential Functions---------------------------------------------------//
bool EnemyWave::Initalise(ConfigManager* ConfigMgr, EntityManager* EntityMgr, int WaveNumber)
{
	//Set the entitymanager and validate it
	m_EntityManager = EntityMgr;
	if(m_EntityManager == nullptr)
		return false;

	//Set the ConfigManager and validate it
	m_ConfigManager = ConfigMgr;
	if(m_ConfigManager == nullptr)
		return false;

	//Give the wave its number
	m_iWaveNumber = WaveNumber;

	return true;
}

void EnemyWave::Spawn()
{
	//Add all the enemies that is written in its wave
	std::string Wave = std::to_string(m_iWaveNumber);
	int fire = m_ConfigManager->ReadInt("EnemyFireWave" + Wave);
	int water = m_ConfigManager->ReadInt("EnemyWaterWave" + Wave);
	int wood = m_ConfigManager->ReadInt("EnemyWoodWave" + Wave);

	for(int i = 0; i < fire; i++)
	{
		m_EntityManager->AttachEntity(FIREFOE, Vector2(m_ConfigManager->ReadInt("WaveWidth") + 320, rand() % m_ConfigManager->ReadInt("WindowHeight")), FIRE);
	}
	
	for(int i = 0; i < water; i++)
	{
		m_EntityManager->AttachEntity(WATERFOE, Vector2(m_ConfigManager->ReadInt("WaveWidth") + 320, rand() % m_ConfigManager->ReadInt("WindowHeight")), WATER);
	}

	for(int i = 0; i < wood; i++)
	{
		m_EntityManager->AttachEntity(WOODFOE, Vector2(m_ConfigManager->ReadInt("WaveWidth") + 320, rand() % m_ConfigManager->ReadInt("WindowHeight")), WOOD);
	}

	m_bSpawned = true;
}

//----------------------End of Essential Functions-------------------------------------------//

//----------------------Access Functions-----------------------------------------------------//

bool EnemyWave::IsSpawned()
{
	return m_bSpawned;
}

int EnemyWave::GetWaveNumber()
{
	return m_iWaveNumber;
}

//----------------------End of Access Functions----------------------------------------------//