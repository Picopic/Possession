//EnemyWaves.cpp

#include "stdafx.h"
#include "EnemyWaves.h"
#include "FireEnemyObject.h"
#include "WaterEnemyObject.h"
#include "WoodEnemyObject.h"
#include "EntityManager.h"
#include "ConfigManager.h"


EnemyWaves::EnemyWaves(EntityManager* em, ConfigManager* config_mgr){
	SpawnTimer = 1024;
	PreviousPlayerX = 0;
	PlayerWalkDistance = 0;
	wavenumber = 0;
	entity_manager = em;

	currentWave.fire = 0;
	currentWave.water = 0;
	currentWave.wood = 0;
	currentWave.altar = 0;

	config_manager = config_mgr;
}


EnemyWaves::~EnemyWaves(){
	if (entity_manager!=nullptr){
		entity_manager = nullptr;
	}
	if(config_manager != nullptr)
		config_manager = nullptr;
}

void EnemyWaves::Restart()
{
	wavenumber = 0;
	PlayerWalkDistance = 0.0f;
	PreviousPlayerX = 0.0f;
}

//Tar en parameter; fire, water eller wood och spawnar den den blir tillsagd att spawna:
void EnemyWaves::CreateEnemies(){

	float spawnX = PreviousPlayerX + 650;

	//enemies.x �r fireleementals
	for (int i = 0; i < currentWave.fire; i++){
		//RANDOMFUNKTION = (rand()%(MAXV�RDET-(MINIMUMV�RDE)+1))+(MINIMUMV�RDE);
		//l�ggs in i varje for nedan f�r varierande spawn-positions-intervall
		//int randomspawnposX = (rand()%(740-(640)+1))+(640);
		//int randomspawnposY = (rand()%(640-(290)+1))+(290);
		float spawnY = rand()%400 + 400;

		entity_manager->AttachEntity(FIREFOE, Vector2(spawnX, spawnY), FIRE);
	}

	//enemies.y �r waterelementals
	for (int i = 0; i < currentWave.water; i++){
		//RANDOMFUNKTION = (rand()%(MAXV�RDET-(MINIMUMV�RDE)+1))+(MINIMUMV�RDE);
		//l�ggs in i varje for nedan f�r varierande spawn-positions-intervall
		//int randomspawnposX = (rand()%(640-(500)+1))+(500);
		//int randomspawnposY = (rand()%(400-(290)+1))+(290);
		float spawnY = rand()%400 + 400;
			
		entity_manager->AttachEntity(WATERFOE, Vector2(spawnX, spawnY), WATER);
	}

	for(int i = 0; i < currentWave.wood; i++)
	{
		//int spawnX = (rand()%(640-(500)+1))+500;
		//int spawnY = (rand()%(250-(150)+1))+(150);
		float spawnY = rand()%400 + 400;

		entity_manager->AttachEntity(WOODFOE, Vector2(spawnX, spawnY), WOOD);
	}

	for(int i = 0; i < currentWave.altar; i++)
	{
		entity_manager->AttachAltar(ALTAR, NONE, Vector2(spawnX, 300)); //FIXA X OCH Y-V�RDEN
	}

};

//Returnerar true n�r det �r dags att spawna fiender; n�r PlayerWalkDistance uppn�tt sitt m�l som �r SpawnTimer "ringer" alarmet SpawnTimerAlarm! :D :D :D
void EnemyWaves::SpawnTimerAlarm(float CurrentPlayerX){
	float DeltaX = CurrentPlayerX - PreviousPlayerX;
	PreviousPlayerX = CurrentPlayerX;
	PlayerWalkDistance +=DeltaX;

	if(PlayerWalkDistance > SpawnTimer)
	{
		PlayerWalkDistance=0;
		wave();
		CreateEnemies();
	}

};

bool EnemyWaves::initialize(){
	return false;
}

//H�r skr�ddarsyr vi hur varje v�g ser ut:
void EnemyWaves::wave(){
	wavenumber++;

	std::string wave = std::to_string(wavenumber);
	
	currentWave.fire = config_manager->ReadInt("wave" + wave + "fire");
	currentWave.water = config_manager->ReadInt("wave" + wave + "water");
	currentWave.wood = config_manager->ReadInt("wave" + wave + "wood");
	currentWave.altar = config_manager->ReadInt("wave" + wave + "altar");
}