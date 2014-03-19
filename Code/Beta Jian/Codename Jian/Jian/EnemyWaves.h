//EnemyWaves.h

#pragma once

#include "stdafx.h"

class Entity;
class EntityManager;
class ConfigManager;

class EnemyWaves{
private:
	//position ska randomisera y-och x inom visst intervall så att fienderna klumpas ihop på ett snyggt sätt:
	sf::Vector2f position;

	//x-värde som bestämmer vars enemywaven spawnar:
	float WaveSpawnX;

	//För att veta var spelaren var förut:
	float PreviousPlayerX;

	//x-värde som kollar hur långt spelaren gått till höger:
	//Det blir PlayerWalkDistance += CurrentPlayerX - PreviousPlayerX 
	float PlayerWalkDistance;

	//värde/timer som säger hur långt spelaren ska gå innan nästa wave spawnar:
	float SpawnTimer;

	

	int wavenumber;

	EntityManager* entity_manager;
	ConfigManager* config_manager;

public:
	EnemyWaves(EntityManager* em, ConfigManager* config_mgr);
	~EnemyWaves();
	
	//Tar en parameter; fire, water eller wood och spawnar den den blir tillsagd att spawna:
	void CreateEnemies(sf::Vector3i enemies);

	//Returnerar true när det är dags att spawna fiender; när PlayerWalkDistance uppnått sitt mål som är SpawnTimer "ringer" alarmet SpawnTimerAlarm! :D :D :D
	void SpawnTimerAlarm(float CurrentPlayerX);

	bool initialize();

	void Restart();

	//funktion som beskriver hur våg ser ut
	sf::Vector3i wave();
};