//ObjectWave.h

#pragma once

//Forward declared classes
class Entity;
class ConfigManager;
class EntityManager;

class ObjectWave
{
public:
	//Constructor for initalising the basic components
	ObjectWave();
	//Deconstructor that cleanup the pointers
	~ObjectWave();

	//Initialise the more essential components
	bool Initalise(ConfigManager* ConfigMgr, EntityManager* EntityMgr, int WaveNumber);

	//Activate the wave
	void Activate();

	//Unactivate the wave
	void UnActivate();

	//Access functions
	bool IsActive();
private:
	//Enables adding objects to the game entites pool
	EntityManager* m_EntityManager;

	//Enables easy access to certain variables
	//Such as WindowWidth
	ConfigManager* m_ConfigManager;

	//Wave active state
	bool m_bActive;

	//The number of the wave
	int m_iWaveNumber;

	//Local pool of entities
	std::vector<Entity*> WaveObjects;
};