//EnemyWaves.cpp

#include "stdafx.h"
#include "EnemyWaves.h"
#include "FireEnemyObject.h"
#include "WaterEnemyObject.h"
//#include "WoodEnemyObject.h"
#include "EntityManager.h"


EnemyWaves::EnemyWaves(EntityManager* em){
	SpawnTimer = 1024;
	PreviousPlayerX = 0;
	PlayerWalkDistance = 0;
	wavenumber = 0;
	entity_manager = em;
}


EnemyWaves::~EnemyWaves(void){
	if (entity_manager!=nullptr){
		delete entity_manager; //Om det blir error kolla h�r
		entity_manager = nullptr;
	}
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
	
	//f�rklaring: sf::Vector31(X, Y, Z) d�r:
	//X = FIRE, Y = WATER, Z= WOOD
	if (wavenumber ==1){
		return sf::Vector3i(2,0,0);
	}

	if (wavenumber ==2){
		return sf::Vector3i(3,0,0);
	}

	if (wavenumber ==3){
		return sf::Vector3i(3,0,0);
	}

	if (wavenumber ==4){
		return sf::Vector3i(4,0,0);
	}

	if (wavenumber <1 && wavenumber> 4){
		return sf::Vector3i (0,0,0);
	}
	return sf::Vector3i(0,0,0);
}