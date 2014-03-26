//ObjectWave.cpp

#include "stdafx.h"

//Forward declared classes
#include "Entity.h"
#include "ConfigManager.h"
#include "EntityManager.h"

#include "ObjectWave.h"

//-----------------------Constructors and Destructors----------------------------------------//
ObjectWave::ObjectWave()
{
	m_EntityManager = nullptr;
	m_ConfigManager = nullptr;

	m_iWaveNumber = 0;
	m_bActive = false;
}

ObjectWave::~ObjectWave()
{
	//Set the entitymanager to null
	if(m_EntityManager != nullptr)
		m_EntityManager = nullptr;

	//Set the ConfigManager to null
	if(m_ConfigManager != nullptr)
		m_ConfigManager = nullptr;

	//Clear the array of Objects
	for(int i = 0; i < WaveObjects.size(); i++)
	{
		if(WaveObjects[i] != nullptr)
			WaveObjects[i] = nullptr;
	}
}
//----------------------End of Constructors and Destructors-----------------------------------//

//----------------------Essential Functions---------------------------------------------------//
bool ObjectWave::Initalise(ConfigManager* ConfigMgr, EntityManager* EntityMgr, int WaveNumber)
{
	//Set the EntityManager and validate it
	m_EntityManager = EntityMgr;
	if(m_EntityManager == nullptr)
		return false;

	//Set the ConfigManager and validate it
	m_ConfigManager = ConfigMgr;
	if(m_ConfigManager == nullptr)
		return false;

	//Set the wavenumber
	m_iWaveNumber = WaveNumber;

	return true;
}

void ObjectWave::Activate()
{
	//Set a string value to the number
	std::string Wave = std::to_string(m_iWaveNumber);

	//How many objects are their in the current wave?
	int NumberOfObjects = m_ConfigManager->ReadInt("NumberOfObjectsWave" + Wave);

	//Initiate all the objects
	for(int i = 0; i < NumberOfObjects; i++)
	{
		std::string ObjectNumber = std::to_string(i);

		m_EntityManager->AttachStaticObject(m_ConfigManager, "Object" + ObjectNumber + "Wave" + Wave);
		WaveObjects.push_back(m_EntityManager->game_entities[m_EntityManager->game_entities.size() - 1]);
	}
}

void ObjectWave::UnActivate()
{
	//First change Active status
	m_bActive = false;

	//Then flag all the entities related to this wave
	//So they get deleted
	for(int i = 0; i < WaveObjects.size(); i++)
	{
		WaveObjects[i]->FlagEntity();
		WaveObjects[i] = nullptr;
	}
	WaveObjects.clear();
}

//----------------------End of Essential Functions-------------------------------------------//

//----------------------Access Functions-----------------------------------------------------//
bool ObjectWave::IsActive()
{
	return m_bActive;
}

//----------------------End of Access Functions----------------------------------------------//