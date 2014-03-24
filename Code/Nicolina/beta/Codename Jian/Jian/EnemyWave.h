//EnemyWave.h

#pragma once
class Entity;
class ConfigManager;
class EntityManager;

class EnemyWave
{
public:
	//Constructor for initalising the basic components
	EnemyWave();
	//Deconstructor that cleanup the pointers
	~EnemyWave();
	
	//Initialise the more essential components
	bool Initalise(ConfigManager* ConfigMgr, EntityManager* EntityMgr, int WaveNumber);

	//Spawn the wave
	void Spawn();

	//Access Functions
	bool IsSpawned();
	int GetWaveNumber();
private:
	//Enables the adding of objects to the game entities pool
	EntityManager* m_EntityManager;

	//Enables more flexibility with screen height etc
	ConfigManager* m_ConfigManager;

	//Whether this wave has been spawned or not
	bool m_bSpawned;

	//The number of the wave
	int m_iWaveNumber;

	//Local pool of entities
	std::vector<Entity*> WaveEnemies;
};