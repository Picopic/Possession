//EnemyWaves.h

#pragma once

#include "stdafx.h"

class Entity;
class EntityManager;
class ConfigManager;

class EnemyWaves{
private:
	//position ska randomisera y-och x inom visst intervall s� att fienderna klumpas ihop p� ett snyggt s�tt:
	sf::Vector2f position;

	//x-v�rde som best�mmer vars enemywaven spawnar:
	float WaveSpawnX;

	//F�r att veta var spelaren var f�rut:
	float PreviousPlayerX;

	//x-v�rde som kollar hur l�ngt spelaren g�tt till h�ger:
	//Det blir PlayerWalkDistance += CurrentPlayerX - PreviousPlayerX 
	float PlayerWalkDistance;

	//v�rde/timer som s�ger hur l�ngt spelaren ska g� innan n�sta wave spawnar:
	float SpawnTimer;

	

	int wavenumber;

	EntityManager* entity_manager;
	ConfigManager* config_manager;

public:
	EnemyWaves(EntityManager* em, ConfigManager* config_mgr);
	~EnemyWaves();
	
	//Tar en parameter; fire, water eller wood och spawnar den den blir tillsagd att spawna:
	void CreateEnemies(sf::Vector3i enemies);

	//Returnerar true n�r det �r dags att spawna fiender; n�r PlayerWalkDistance uppn�tt sitt m�l som �r SpawnTimer "ringer" alarmet SpawnTimerAlarm! :D :D :D
	void SpawnTimerAlarm(float CurrentPlayerX);

	bool initialize();

	void Restart();

	//funktion som beskriver hur v�g ser ut
	sf::Vector3i wave();
};