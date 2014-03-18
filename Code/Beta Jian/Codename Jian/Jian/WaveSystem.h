//WaveSystem.h

#pragma once

//Forward declard classes
class ObjectWave;
class EnemyWave;

class ConfigManager;
class EntityManager;

class WaveSystem
{
public:
	//Constructor that handles basic initiation
	WaveSystem();
	//Destructor that handles the cleanup
	~WaveSystem();

	//Initalise takes care of initialising the more
	//essential components
	bool Initalise(ConfigManager* ConfigMgr, EntityManager* EntityMgr);
	
	//See if it is time to change wave
	bool ChangeWave(float PlayerDeltaX);
private:
	//The length of a one wave
	float m_fWidth;
	//How far the player has walked
	float m_fPlayerX;

	//Reading from files
	ConfigManager* m_ConfigManager;

	//Adding objects to the game
	EntityManager* m_EntityManager;

	//Vectors of waves
	std::vector<ObjectWave*> m_ObjectWaves;
	std::vector<EnemyWave*> m_EnemyWaves;

	//The current wave that the player is in
	int m_iCurrentWave;

	//The number of waves in the game
	int m_iNumberOfWaves;
};