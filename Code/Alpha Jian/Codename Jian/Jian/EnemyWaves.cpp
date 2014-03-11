//EnemyWaves.cpp

#include "stdafx.h"
#include "EnemyWaves.h"
#include "FireEnemyObject.h"
#include "WaterEnemyObject.h"
//#include "WoodEnemyObject.h"
#include "EntityManager.h"
#include "ConfigManager.h"


EnemyWaves::EnemyWaves(EntityManager* em, ConfigManager* config_mgr){
	SpawnTimer = 1024;
	PreviousPlayerX = 0;
	PlayerWalkDistance = 0;
	wavenumber = 0;
	entity_manager = em;

	config_manager = config_mgr;
}


EnemyWaves::~EnemyWaves(void){
	if (entity_manager!=nullptr){
		delete entity_manager; //Om det blir error kolla h�r
		entity_manager = nullptr;
	}
	if(config_manager != nullptr)
		config_manager = nullptr;
}

//Tar en parameter; fire, water eller wood och spawnar den den blir tillsagd att spawna:
void EnemyWaves::CreateEnemies(sf::Vector3i enemies){

		//enemies.x �r fireleementals
		for (int i = 0; i < enemies.x; i++){
			//RANDOMFUNKTION = (rand()%(MAXV�RDET-(MINIMUMV�RDE)+1))+(MINIMUMV�RDE);
			//l�ggs in i varje for nedan f�r varierande spawn-positions-intervall
			int randomspawnposX = (rand()%(740-(640)+1))+(640);
			int randomspawnposY = (rand()%(640-(290)+1))+(290);

			entity_manager->	AttachEntity(FIREFOE, Vector2(PreviousPlayerX+randomspawnposX, randomspawnposY), 100, 80, FIRE);
		}

		//enemies.y �r waterelementals
		for (int i = 0; i < enemies.y; i++){
			//RANDOMFUNKTION = (rand()%(MAXV�RDET-(MINIMUMV�RDE)+1))+(MINIMUMV�RDE);
			//l�ggs in i varje for nedan f�r varierande spawn-positions-intervall
			int randomspawnposX = (rand()%(640-(500)+1))+(500);
			int randomspawnposY = (rand()%(640-(290)+1))+(290);
			
			//BYT UT DESSA MOT WATERFOE N�R DE �R IMPLEMENTERADE:
			entity_manager->	AttachEntity(FIREFOE, Vector2(PreviousPlayerX+randomspawnposX, randomspawnposY), 100, 80, FIRE);
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
		CreateEnemies(wave());
	}

};

bool EnemyWaves::initialize(){
	return false;
}

//H�r skr�ddarsyr vi hur varje v�g ser ut:
sf::Vector3i EnemyWaves::wave(){
	wavenumber += 1;

	int fire = 0;
	int water = 0;
	int wood = 0;
	
	//f�rklaring: sf::Vector31(X, Y, Z) d�r:
	//X = FIRE, Y = WATER, Z= WOOD
	if (wavenumber ==1){
		fire = config_manager->ReadInt("wave1fire");
		water = config_manager->ReadInt("wave1water");
		wood = config_manager->ReadInt("wave1wood");

		return sf::Vector3i(fire,water,wood);
	}

	if (wavenumber ==2){
		fire = config_manager->ReadInt("wave2fire");
		water = config_manager->ReadInt("wave2water");
		wood = config_manager->ReadInt("wave2wood");

		return sf::Vector3i(fire,water,wood);
	}

	if (wavenumber ==3){
		fire = config_manager->ReadInt("wave3fire");
		water = config_manager->ReadInt("wave3water");
		wood = config_manager->ReadInt("wave3wood");

		return sf::Vector3i(fire,water,wood);
	}

	if (wavenumber ==4){
		fire = config_manager->ReadInt("wave4fire");
		water = config_manager->ReadInt("wave4water");
		wood = config_manager->ReadInt("wave4wood");

		return sf::Vector3i(fire,water,wood);
	}

	//kommer den h�r ens kunna h�nda :?
	if (wavenumber <1 && wavenumber> 4){
		return sf::Vector3i(fire,water,wood);
	}
	return sf::Vector3i(fire,water,wood);
}