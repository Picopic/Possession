//EntityManager.cpp

#include "stdafx.h"

#include "StaticObject.h"
#include "EntityManager.h"


EntityManager::EntityManager()
{

}

EntityManager::EntityManager(SpriteManager* sprite_mgr, SoundManager* sound_mgr)
{
	sprite_manager = sprite_mgr;
	sound_manager = sound_mgr;
	config_manager = new ConfigManager;
	GAMEOVER = false;
}

EntityManager::~EntityManager()
{

}

void EntityManager::Init(EnemyWaves* enemywavesptr)
{
	//ConfigManager initalisation
	config_manager = new ConfigManager;
	config_manager->Initialise("../data/Configs/");
	config_manager->ReadFile("Player.txt");
	config_manager->ReadFile("Fire Enemy.txt");
	config_manager->ReadFile("Projectile.txt");
	config_manager->ReadFile("Water Enemy.txt");
	config_manager->ReadFile("Wood Enemy.txt");
	config_manager->ReadFile("LostSoul.txt");

	//Spritesheet width and height
	playerheight = 252;
	playerwidth = 252;
	playerspritesheet = "MC SPRITESHEET 252p w transparency.png";

	fireprojectileheight = 250;
	fireprojectilewidth = 180;
	waterprojectileheight = 250;
	waterprojectilewidth = 180;
	woodprojectileheight = 250;
	woodprojectilewidth = 180;

	fireprojectilespritesheet = "Projectiles 180x250p.png";
	waterprojectilespritesheet = "Projectiles 180x250p.png";
	woodprojectilespritesheet = "Projectiles 180x250p.png";

	fireheight = 315;
	firewidth = 315;
	firespritesheet = "FIRE SPRITESHEET 315p.png";

	waterheight = 315;
	waterwidth = 315;
	waterspritesheet = "WATER SPRITESHEET 315p.png";

	woodheight = 405;
	woodwidth = 495;
	woodspritesheet = "WOOD SPRITESHEET 495x405p.png";

	lostsoulheight = 110;
	lostsoulwidth = 100;
	lostsoulspritesheet = "Lost Souls Spritesheet.png";

	//Enemy wave spawn:
	waves = enemywavesptr;

	//Collisionmap initalisation
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (PLAYER, WATERFOE), 0));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (PLAYER, WOODFOE), 1));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (PLAYER, FIREFOE), 2));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (PLAYER, WATERFOEBULLET), 3));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (PLAYER, WOODFOEBULLET), 4));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (PLAYER, FIREFOEBULLET), 5));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (PLAYER, LOSTSOUL), 6));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (PLAYER, ALTAR), 7));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (WATERFOE, FRIENDBULLET), 8));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (WOODFOE, FRIENDBULLET), 9));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (FIREFOE, FRIENDBULLET), 10));
	//Wall collision
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (WALL, PLAYER), 11));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (WALL, FIREFOE), 12));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (WALL, WATERFOE), 13));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (WALL, WOODFOE), 14));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (WALL, FRIENDBULLET), 15));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (WALL, FIREFOEBULLET), 16));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (WALL, WATERFOEBULLET), 17));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (WALL, WOODFOEBULLET), 18));

	//Enemy collision
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (FIREFOE, WATERFOE), 19));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (FIREFOE, WOODFOE), 20));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (WOODFOE, WATERFOE), 21));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (FIREFOE, FIREFOE), 22));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (WOODFOE, WOODFOE), 23));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (WATERFOE, WATERFOE), 24));

	//Static objects
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (STATICOBJECT, WATERFOE), 25));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (STATICOBJECT, FIREFOE), 26));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (STATICOBJECT, WOODFOE), 27));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (STATICOBJECT, PLAYER), 28));
}

void EntityManager::AttachEntity(Alignment entity_name, Vector2 position, Type type)
{
	/*
	create new entity, appropriate to the string that followed
	*/
	switch(entity_name)
	{
	case PLAYER:

		game_entities.push_back(new PlayerObject(config_manager));

		game_entities[game_entities.size() - 1]->AddAnimation(IDLERIGHT, sprite_manager->Load(playerspritesheet, 7, 20, playerwidth, playerheight, 0, playerheight*0));
		game_entities[game_entities.size() - 1]->AddAnimation(IDLELEFT, sprite_manager->Load(playerspritesheet, 7, 20, playerwidth, playerheight, 0, playerheight*7));

		game_entities[game_entities.size() - 1]->AddAnimation(ATTACKRIGHT, sprite_manager->Load(playerspritesheet, 5, 20, playerwidth, playerheight, 0, playerheight*2));
		game_entities[game_entities.size() - 1]->AddAnimation(ATTACKLEFT, sprite_manager->Load(playerspritesheet, 5, 20, playerwidth, playerheight, 0, playerheight*9));

		game_entities[game_entities.size() - 1]->AddAnimation(WALKRIGHT, sprite_manager->Load(playerspritesheet, 8, 20, playerwidth, playerheight, 0, playerheight*1));
		game_entities[game_entities.size() - 1]->AddAnimation(WALKLEFT, sprite_manager->Load(playerspritesheet, 8, 20, playerwidth, playerheight, 0, playerheight*8));

		game_entities[game_entities.size() - 1]->AddAnimation(RELEASERIGHT, sprite_manager->Load(playerspritesheet, 6, 20, playerwidth, playerheight, playerwidth*0, playerheight*3));
		game_entities[game_entities.size() - 1]->AddAnimation(RELEASELEFT, sprite_manager->Load(playerspritesheet, 6, 20, playerwidth, playerheight, playerwidth*0, playerheight*10));

		game_entities[game_entities.size() - 1]->AddAnimation(EATRIGHT, sprite_manager->Load(playerspritesheet, 6, 20, playerwidth, playerheight, playerwidth*0, playerheight*4));
		game_entities[game_entities.size() - 1]->AddAnimation(EATLEFT, sprite_manager->Load(playerspritesheet, 6, 20, playerwidth, playerheight, playerwidth*0, playerheight*11));

		game_entities[game_entities.size() - 1]->AddAnimation(DEATHRIGHT, sprite_manager->Load(playerspritesheet, 30, 20, playerwidth, playerheight, playerwidth*0, playerheight*5));
		game_entities[game_entities.size() - 1]->AddAnimation(DEATHLEFT, sprite_manager->Load(playerspritesheet, 30, 20, playerwidth, playerheight, playerwidth*0, playerheight*12));

		game_entities[game_entities.size() - 1]->AddAnimation(HITRIGHT, sprite_manager->LoadReversed(playerspritesheet, 3, 3, playerwidth, playerheight, playerwidth*3, playerheight*5));
		game_entities[game_entities.size() - 1]->AddAnimation(HITLEFT, sprite_manager->LoadReversed(playerspritesheet, 3, 3, playerwidth, playerheight, playerwidth*3, playerheight*12));
		
		//sounds
		game_entities[game_entities.size() - 1]->AddSounds(sound_manager);

		game_entities[game_entities.size() - 1]->Init("Player", PLAYER, FIRE);
		break;
	case WATERFOE:
		game_entities.push_back(new WaterEnemyObject(config_manager, position));

		//add animations
		//left
		game_entities[game_entities.size() - 1]->AddAnimation(IDLELEFT, sprite_manager->Load(waterspritesheet, 5, 4, waterwidth, waterheight, 0, 0));
		game_entities[game_entities.size() - 1]->AddAnimation(ATTACKLEFT, sprite_manager->Load(waterspritesheet, 6, 4, waterwidth, waterheight, 0, 4*waterheight));
		game_entities[game_entities.size() - 1]->AddAnimation(DEATHLEFT, sprite_manager->Load(waterspritesheet, 8, 4, waterwidth, waterheight, 0, 6*waterheight));
		game_entities[game_entities.size() - 1]->AddAnimation(HITLEFT, sprite_manager->LoadReversed(waterspritesheet, 3, 3, waterwidth, waterheight, waterwidth*3, 6*waterheight));

		//right
		game_entities[game_entities.size() - 1]->AddAnimation(IDLERIGHT, sprite_manager->Load(waterspritesheet, 5, 4, waterwidth, waterheight, 0, 8*waterheight));
		game_entities[game_entities.size() - 1]->AddAnimation(ATTACKRIGHT, sprite_manager->Load(waterspritesheet, 6, 4, waterwidth, waterheight, 0, 12*waterheight));
		game_entities[game_entities.size() - 1]->AddAnimation(DEATHRIGHT, sprite_manager->Load(waterspritesheet, 8, 4, waterwidth, waterheight, 0, 14*waterheight));
		game_entities[game_entities.size() - 1]->AddAnimation(HITRIGHT, sprite_manager->LoadReversed(waterspritesheet, 3, 3, waterwidth, waterheight, waterwidth*3, 14*waterheight));

		game_entities[game_entities.size()-1]->Init("Water enemy", entity_name, type);
		break;
	case FIREFOE:
		game_entities.push_back(new FireEnemyObject(config_manager, position));
		//left
		game_entities[game_entities.size()-1]->AddAnimation(IDLELEFT, sprite_manager->Load(firespritesheet, 4, 4, firewidth, fireheight, 0, fireheight*0));
		game_entities[game_entities.size()-1]->AddAnimation(WALKLEFT, sprite_manager->Load(firespritesheet, 4, 4, firewidth, fireheight, 0, fireheight*1));
		game_entities[game_entities.size()-1]->AddAnimation(ATTACKLEFT, sprite_manager->Load(firespritesheet, 6, 4, firewidth, fireheight, 0, fireheight*2));
		game_entities[game_entities.size()-1]->AddAnimation(DEATHLEFT, sprite_manager->Load(firespritesheet, 7, 4, firewidth, fireheight, 0, fireheight*4));
		game_entities[game_entities.size()-1]->AddAnimation(HITLEFT, sprite_manager->Load(firespritesheet, 3, 3, firewidth, fireheight, firewidth*0, fireheight*4));

		//right
		game_entities[game_entities.size()-1]->AddAnimation(IDLERIGHT, sprite_manager->Load(firespritesheet, 4, 4, firewidth, fireheight, 0, fireheight*6));
		game_entities[game_entities.size()-1]->AddAnimation(WALKRIGHT, sprite_manager->Load(firespritesheet, 4, 4, firewidth, fireheight, 0, fireheight*7));
		game_entities[game_entities.size()-1]->AddAnimation(ATTACKRIGHT, sprite_manager->Load(firespritesheet, 6, 4, firewidth, fireheight, 0, fireheight*8));
		game_entities[game_entities.size()-1]->AddAnimation(DEATHRIGHT, sprite_manager->Load(firespritesheet, 7, 4, firewidth, fireheight, firewidth*3, fireheight*10));
		game_entities[game_entities.size()-1]->AddAnimation(HITLEFT, sprite_manager->Load(firespritesheet, 3, 3, firewidth, fireheight, firewidth*0, fireheight*10));

		game_entities[game_entities.size()-1]->Init("Fire enemy", entity_name, type);
		break;
	case WOODFOE:
		game_entities.push_back(new WoodEnemyObject(config_manager, position));
		//left
		game_entities[game_entities.size()-1]->AddAnimation(IDLELEFT, sprite_manager->Load(woodspritesheet, 6, 9, woodwidth, woodheight, 0, 0*woodheight));
		game_entities[game_entities.size()-1]->AddAnimation(WALKLEFT, sprite_manager->Load(woodspritesheet, 8, 9, woodwidth, woodheight, 0, 1*woodheight));
		game_entities[game_entities.size()-1]->AddAnimation(ATTACKLEFT, sprite_manager->Load(woodspritesheet, 9, 9, woodwidth, woodheight, 0, 2*woodheight));
		game_entities[game_entities.size()-1]->AddAnimation(DEATHLEFT, sprite_manager->Load(woodspritesheet, 9, 9, woodwidth, woodheight, 0, 3*woodheight));
		game_entities[game_entities.size()-1]->AddAnimation(HITLEFT, sprite_manager->Load(woodspritesheet, 9, 9, woodwidth, woodheight, woodwidth*0, 3*woodheight));

		//right
		game_entities[game_entities.size()-1]->AddAnimation(IDLERIGHT, sprite_manager->Load(woodspritesheet, 6, 9, woodwidth, woodheight, 0, 4*woodheight));
		game_entities[game_entities.size()-1]->AddAnimation(WALKRIGHT, sprite_manager->Load(woodspritesheet, 8, 9, woodwidth, woodheight, 0, 5*woodheight));
		game_entities[game_entities.size()-1]->AddAnimation(ATTACKRIGHT, sprite_manager->Load(woodspritesheet, 9, 9, woodwidth, woodheight, 0, 6*woodheight));
		game_entities[game_entities.size()-1]->AddAnimation(DEATHRIGHT, sprite_manager->Load(woodspritesheet, 9, 9, woodwidth, woodheight, 0, 7*woodheight));
		game_entities[game_entities.size()-1]->AddAnimation(HITRIGHT, sprite_manager->Load(woodspritesheet, 9, 9, woodwidth, woodheight, woodwidth*0, 7*woodheight));

		game_entities[game_entities.size()-1]->Init("wood enemy", entity_name, type);
		break;
	}

}

void EntityManager::DetachEntity(int entity_index)
{
	/*
	Delete the entity, appropriate to the string that followed
	*/
}

void EntityManager::ClearGameEntities()
{
	for(int i = 0; i < game_entities.size(); i ++)
	{
		delete game_entities[i];
		game_entities[i] = nullptr;
		game_entities.erase(game_entities.begin() + i);
	}

	game_entities.clear();
}

void EntityManager::CreatePlayer()
{
	GAMEOVER = false;
	AttachEntity(PLAYER, Vector2(400, 400), FIRE);
}

void EntityManager::AttachProjectile(Alignment entity_name, Entity* shooter, int width, int height, Type entity_type, Vector2 entity_direction, bool DoubleShot)
{
	Vector2 position;
	float projectileHeight;
	switch (entity_type)
	{
	case FIRE:

		if(DoubleShot)
		{
			projectileHeight = config_manager->ReadFloat("fireprojectileheight");
			if(entity_direction.x == 1)
			{
				position.x = shooter->getPosition().x + shooter->GetSprite()->getTextureRect().width/2;
				position.y = (shooter->getCollider()->position.y + shooter->getCollider()->extension.y) - 250 + (projectileHeight/2);
				game_entities.push_back(new Projectile(shooter, entity_type, config_manager, Vector2(1, 0.1), DoubleShot, position));
			}
			else if(entity_direction.x == -1)
			{
				position.x = shooter->getPosition().x;
				position.y = (shooter->getCollider()->position.y + shooter->getCollider()->extension.y) - 250 + (projectileHeight/2);
				game_entities.push_back(new Projectile(shooter, entity_type, config_manager, Vector2(-1, 0.1), DoubleShot, position));
			}

			


			//What animations
			if(entity_direction.x == 1)
			{
				game_entities[game_entities.size() - 1]->AddAnimation(ATTACKRIGHT, sprite_manager->Load(fireprojectilespritesheet, 4, 4, fireprojectilewidth, fireprojectileheight, fireprojectilewidth*0, fireprojectileheight*1));
				game_entities[game_entities.size() - 1]->AddAnimation(DEATHRIGHT, sprite_manager->Load(fireprojectilespritesheet, 5, 4, fireprojectilewidth, fireprojectileheight, fireprojectilewidth*0, fireprojectileheight*2));
				game_entities[game_entities.size() - 1]->AddAnimation(FADEOUTRIGHT, sprite_manager->Load(fireprojectilespritesheet, 4, 4, fireprojectilewidth, fireprojectileheight, fireprojectilewidth*0, fireprojectileheight*0));
			}
			else if(entity_direction.x == -1)
			{
				game_entities[game_entities.size() - 1]->AddAnimation(ATTACKLEFT, sprite_manager->Load(fireprojectilespritesheet, 4, 4, fireprojectilewidth, fireprojectileheight, fireprojectilewidth*0, fireprojectileheight*5));
				game_entities[game_entities.size() - 1]->AddAnimation(DEATHLEFT, sprite_manager->Load(fireprojectilespritesheet, 5, 4, fireprojectilewidth, fireprojectileheight, fireprojectilewidth*0, fireprojectileheight*6));
				game_entities[game_entities.size() - 1]->AddAnimation(FADEOUTLEFT, sprite_manager->Load(fireprojectilespritesheet, 4, 4, fireprojectilewidth, fireprojectileheight, fireprojectilewidth*0, fireprojectileheight*4));
			}
			game_entities[game_entities.size() -1]->setplayer(game_entities[0]);

			game_entities[game_entities.size() -1]->Init("FIRE", entity_name, entity_type);

			//Second attack

			if(entity_direction.x == 1)
			{
				position.x = shooter->getPosition().x + shooter->GetSprite()->getTextureRect().width/2;
				position.y = (shooter->getCollider()->position.y + shooter->getCollider()->extension.y) - 250 - (projectileHeight/2);
				game_entities.push_back(new Projectile(shooter, entity_type, config_manager, Vector2(1, -0.1), DoubleShot, position));
			}
			else if(entity_direction.x == -1)
			{
				position.x = shooter->getPosition().x;
				position.y = (shooter->getCollider()->position.y + shooter->getCollider()->extension.y) - 250 - (projectileHeight/2);
				game_entities.push_back(new Projectile(shooter, entity_type, config_manager, Vector2(-1, -0.1), DoubleShot, position));
			}

			//What animations
			if(entity_direction.x == 1)
			{
				game_entities[game_entities.size() - 1]->AddAnimation(ATTACKRIGHT, sprite_manager->Load(fireprojectilespritesheet, 4, 4, fireprojectilewidth, fireprojectileheight, fireprojectilewidth*0, fireprojectileheight*1));
				game_entities[game_entities.size() - 1]->AddAnimation(DEATHRIGHT, sprite_manager->Load(fireprojectilespritesheet, 5, 4, fireprojectilewidth, fireprojectileheight, fireprojectilewidth*0, fireprojectileheight*2));
				game_entities[game_entities.size() - 1]->AddAnimation(FADEOUTRIGHT, sprite_manager->Load(fireprojectilespritesheet, 4, 4, fireprojectilewidth, fireprojectileheight, fireprojectilewidth*0, fireprojectileheight*0));
			}
			else if(entity_direction.x == -1)
			{
				game_entities[game_entities.size() - 1]->AddAnimation(ATTACKLEFT, sprite_manager->Load(fireprojectilespritesheet, 4, 4, fireprojectilewidth, fireprojectileheight, fireprojectilewidth*0, fireprojectileheight*5));
				game_entities[game_entities.size() - 1]->AddAnimation(DEATHLEFT, sprite_manager->Load(fireprojectilespritesheet, 5, 4, fireprojectilewidth, fireprojectileheight, fireprojectilewidth*0, fireprojectileheight*6));
				game_entities[game_entities.size() - 1]->AddAnimation(FADEOUTLEFT, sprite_manager->Load(fireprojectilespritesheet, 4, 4, fireprojectilewidth, fireprojectileheight, fireprojectilewidth*0, fireprojectileheight*4));
			}
			game_entities[game_entities.size() -1]->setplayer(game_entities[0]);

			game_entities[game_entities.size() -1]->Init("FIRE", entity_name, entity_type);
		}
		else
		{
			if(entity_direction.x == 1)
			{
				position.x = shooter->getPosition().x + shooter->GetSprite()->getTextureRect().width/2;
				position.y = (shooter->getCollider()->position.y + shooter->getCollider()->extension.y) - 250;
			}
			else if(entity_direction.x == -1)
			{
				position.x = shooter->getPosition().x;
				position.y = (shooter->getCollider()->position.y + shooter->getCollider()->extension.y) - 250;
			}

			game_entities.push_back(new Projectile(shooter, entity_type, config_manager, Vector2(entity_direction.x, 0), DoubleShot, position));


			//What animations
			if(entity_direction.x == 1)
			{
				game_entities[game_entities.size() - 1]->AddAnimation(ATTACKRIGHT, sprite_manager->Load(fireprojectilespritesheet, 4, 4, fireprojectilewidth, fireprojectileheight, fireprojectilewidth*0, fireprojectileheight*1));
				game_entities[game_entities.size() - 1]->AddAnimation(DEATHRIGHT, sprite_manager->Load(fireprojectilespritesheet, 5, 4, fireprojectilewidth, fireprojectileheight, fireprojectilewidth*0, fireprojectileheight*2));
				game_entities[game_entities.size() - 1]->AddAnimation(FADEOUTRIGHT, sprite_manager->Load(fireprojectilespritesheet, 4, 4, fireprojectilewidth, fireprojectileheight, fireprojectilewidth*0, fireprojectileheight*0));
			}
			else if(entity_direction.x == -1)
			{
				game_entities[game_entities.size() - 1]->AddAnimation(ATTACKLEFT, sprite_manager->Load(fireprojectilespritesheet, 4, 4, fireprojectilewidth, fireprojectileheight, fireprojectilewidth*0, fireprojectileheight*5));
				game_entities[game_entities.size() - 1]->AddAnimation(DEATHLEFT, sprite_manager->Load(fireprojectilespritesheet, 5, 4, fireprojectilewidth, fireprojectileheight, fireprojectilewidth*0, fireprojectileheight*6));
				game_entities[game_entities.size() - 1]->AddAnimation(FADEOUTLEFT, sprite_manager->Load(fireprojectilespritesheet, 4, 4, fireprojectilewidth, fireprojectileheight, fireprojectilewidth*0, fireprojectileheight*4));
			}
			game_entities[game_entities.size() -1]->setplayer(game_entities[0]);

			game_entities[game_entities.size() -1]->Init("FIRE", entity_name, entity_type);
		}
		break;

	case WATER:

		if(DoubleShot)
		{
			projectileHeight = config_manager->ReadFloat("waterprojectileheight");
			if(entity_direction.x == 1)
			{
				position.x = shooter->getPosition().x + shooter->GetSprite()->getTextureRect().width/2;
				position.y = (shooter->getCollider()->position.y + shooter->getCollider()->extension.y) - 250 + (projectileHeight/2);
				game_entities.push_back(new Projectile(shooter, entity_type, config_manager, Vector2(1, 0.1), DoubleShot, position));
			}
			else if(entity_direction.x == -1)
			{
				position.x = shooter->getPosition().x;
				position.y = (shooter->getCollider()->position.y + shooter->getCollider()->extension.y) - 250 + (projectileHeight/2);
				game_entities.push_back(new Projectile(shooter, entity_type, config_manager, Vector2(-1, 0.1), DoubleShot, position));
			}

			//What animations
			if(entity_direction.x == 1)
			{
				game_entities[game_entities.size() - 1]->AddAnimation(ATTACKRIGHT, sprite_manager->Load(waterprojectilespritesheet, 4, 4, waterprojectilewidth, waterprojectileheight, waterprojectilewidth*8, waterprojectileheight*1));
				game_entities[game_entities.size() - 1]->AddAnimation(DEATHRIGHT, sprite_manager->Load(waterprojectilespritesheet, 5, 4, waterprojectilewidth, waterprojectileheight, waterprojectilewidth*8, waterprojectileheight*2));
				game_entities[game_entities.size() - 1]->AddAnimation(FADEOUTRIGHT, sprite_manager->Load(waterprojectilespritesheet, 4, 4, waterprojectilewidth, waterprojectileheight, waterprojectilewidth*8, waterprojectileheight*0));
			}
			else if(entity_direction.x == -1)
			{
				game_entities[game_entities.size() - 1]->AddAnimation(ATTACKLEFT, sprite_manager->Load(waterprojectilespritesheet, 4, 4, waterprojectilewidth, waterprojectileheight, waterprojectilewidth*8, waterprojectileheight*1));
				game_entities[game_entities.size() - 1]->AddAnimation(DEATHLEFT, sprite_manager->Load(waterprojectilespritesheet, 5, 4, waterprojectilewidth, waterprojectileheight, waterprojectilewidth*8, waterprojectileheight*2));
				game_entities[game_entities.size() - 1]->AddAnimation(FADEOUTLEFT, sprite_manager->Load(waterprojectilespritesheet, 4, 4, waterprojectilewidth, waterprojectileheight, waterprojectilewidth*8, waterprojectileheight*0));
			}

			game_entities[game_entities.size() -1]->setplayer(game_entities[0]);

			game_entities[game_entities.size() -1]->Init("WATER", entity_name, entity_type);

			//Second attack

			if(entity_direction.x == 1)
			{
				position.x = shooter->getPosition().x + shooter->GetSprite()->getTextureRect().width/2;
				position.y = (shooter->getCollider()->position.y + shooter->getCollider()->extension.y) - 250 - (projectileHeight/2);
				game_entities.push_back(new Projectile(shooter, entity_type, config_manager, Vector2(1, -0.1), DoubleShot, position));
			}
			else if(entity_direction.x == -1)
			{
				position.x = shooter->getPosition().x;
				position.y = (shooter->getCollider()->position.y + shooter->getCollider()->extension.y) - 250 - (projectileHeight/2);
				game_entities.push_back(new Projectile(shooter, entity_type, config_manager, Vector2(-1, -0.1), DoubleShot, position));
			}

			//What animations
			if(entity_direction.x == 1)
			{
				game_entities[game_entities.size() - 1]->AddAnimation(ATTACKRIGHT, sprite_manager->Load(waterprojectilespritesheet, 4, 4, waterprojectilewidth, waterprojectileheight, waterprojectilewidth*8, waterprojectileheight*1));
				game_entities[game_entities.size() - 1]->AddAnimation(DEATHRIGHT, sprite_manager->Load(waterprojectilespritesheet, 5, 4, waterprojectilewidth, waterprojectileheight, waterprojectilewidth*8, waterprojectileheight*2));
				game_entities[game_entities.size() - 1]->AddAnimation(FADEOUTRIGHT, sprite_manager->Load(waterprojectilespritesheet, 4, 4, waterprojectilewidth, waterprojectileheight, waterprojectilewidth*8, waterprojectileheight*0));
			}
			else if(entity_direction.x == -1)
			{
				game_entities[game_entities.size() - 1]->AddAnimation(ATTACKLEFT, sprite_manager->Load(waterprojectilespritesheet, 4, 4, waterprojectilewidth, waterprojectileheight, waterprojectilewidth*8, waterprojectileheight*1));
				game_entities[game_entities.size() - 1]->AddAnimation(DEATHLEFT, sprite_manager->Load(waterprojectilespritesheet, 5, 4, waterprojectilewidth, waterprojectileheight, waterprojectilewidth*8, waterprojectileheight*2));
				game_entities[game_entities.size() - 1]->AddAnimation(FADEOUTLEFT, sprite_manager->Load(waterprojectilespritesheet, 4, 4, waterprojectilewidth, waterprojectileheight, waterprojectilewidth*8, waterprojectileheight*0));
			}

			game_entities[game_entities.size() -1]->setplayer(game_entities[0]);

			game_entities[game_entities.size() -1]->Init("WATER", entity_name, entity_type);
		}
		else
		{
			if(entity_direction.x == 1)
			{
				position.x = shooter->getPosition().x + shooter->GetSprite()->getTextureRect().width/2;
				position.y = (shooter->getCollider()->position.y + shooter->getCollider()->extension.y) - 250;
			}
			else if(entity_direction.x == -1)
			{
				position.x = shooter->getPosition().x;
				position.y = (shooter->getCollider()->position.y + shooter->getCollider()->extension.y) - 250;
			}

			game_entities.push_back(new Projectile(shooter, entity_type, config_manager, Vector2(entity_direction.x, 0), DoubleShot, position));

			//What animations
			if(entity_direction.x == 1)
			{
				game_entities[game_entities.size() - 1]->AddAnimation(ATTACKRIGHT, sprite_manager->Load(waterprojectilespritesheet, 4, 4, waterprojectilewidth, waterprojectileheight, waterprojectilewidth*8, waterprojectileheight*1));
				game_entities[game_entities.size() - 1]->AddAnimation(DEATHRIGHT, sprite_manager->Load(waterprojectilespritesheet, 5, 4, waterprojectilewidth, waterprojectileheight, waterprojectilewidth*8, waterprojectileheight*2));
				game_entities[game_entities.size() - 1]->AddAnimation(FADEOUTRIGHT, sprite_manager->Load(waterprojectilespritesheet, 4, 4, waterprojectilewidth, waterprojectileheight, waterprojectilewidth*8, waterprojectileheight*0));
			}
			else if(entity_direction.x == -1)
			{
				game_entities[game_entities.size() - 1]->AddAnimation(ATTACKLEFT, sprite_manager->Load(waterprojectilespritesheet, 4, 4, waterprojectilewidth, waterprojectileheight, waterprojectilewidth*8, waterprojectileheight*1));
				game_entities[game_entities.size() - 1]->AddAnimation(DEATHLEFT, sprite_manager->Load(waterprojectilespritesheet, 5, 4, waterprojectilewidth, waterprojectileheight, waterprojectilewidth*8, waterprojectileheight*2));
				game_entities[game_entities.size() - 1]->AddAnimation(FADEOUTLEFT, sprite_manager->Load(waterprojectilespritesheet, 4, 4, waterprojectilewidth, waterprojectileheight, waterprojectilewidth*8, waterprojectileheight*0));
			}

			game_entities[game_entities.size() -1]->setplayer(game_entities[0]);

			game_entities[game_entities.size() -1]->Init("WATER", entity_name, entity_type);
		}
		
		break;

	case WOOD:
		if(DoubleShot)
		{
			projectileHeight = config_manager->ReadFloat("woodprojectileheight");
			if(entity_direction.x == 1)
			{
				position.x = shooter->getPosition().x + shooter->GetSprite()->getTextureRect().width/2;
				position.y = (shooter->getCollider()->position.y + shooter->getCollider()->extension.y) - 250 + (projectileHeight/2);
				game_entities.push_back(new Projectile(shooter, entity_type, config_manager, Vector2(1, 0.1), DoubleShot, position));
			}
			else if(entity_direction.x == -1)
			{
				position.x = shooter->getPosition().x;
				position.y = (shooter->getCollider()->position.y + shooter->getCollider()->extension.y) - 250 + (projectileHeight/2);
				game_entities.push_back(new Projectile(shooter, entity_type, config_manager, Vector2(-1, 0.1), DoubleShot, position));
			}

			//What animations
			if(entity_direction.x == 1)
			{
				game_entities[game_entities.size() - 1]->AddAnimation(ATTACKRIGHT, sprite_manager->Load(woodprojectilespritesheet, 4, 4, woodprojectilewidth, woodprojectileheight, woodprojectilewidth*4, woodprojectileheight*1));
				game_entities[game_entities.size() - 1]->AddAnimation(DEATHRIGHT, sprite_manager->Load(woodprojectilespritesheet, 5, 4, woodprojectilewidth, woodprojectileheight, woodprojectilewidth*4, woodprojectileheight*2));
				game_entities[game_entities.size() - 1]->AddAnimation(FADEOUTRIGHT, sprite_manager->Load(woodprojectilespritesheet, 4, 4, woodprojectilewidth, woodprojectileheight, woodprojectilewidth*4, woodprojectileheight*0));
			}
			else if(entity_direction.x == -1)
			{
				game_entities[game_entities.size() - 1]->AddAnimation(ATTACKLEFT, sprite_manager->Load(woodprojectilespritesheet, 4, 4, woodprojectilewidth, woodprojectileheight, woodprojectilewidth*4, woodprojectileheight*5));
				game_entities[game_entities.size() - 1]->AddAnimation(DEATHLEFT, sprite_manager->Load(woodprojectilespritesheet, 5, 4, woodprojectilewidth, woodprojectileheight, woodprojectilewidth*4, woodprojectileheight*6));
				game_entities[game_entities.size() - 1]->AddAnimation(FADEOUTLEFT, sprite_manager->Load(woodprojectilespritesheet, 4, 4, woodprojectilewidth, woodprojectileheight, woodprojectilewidth*4, woodprojectileheight*4));
			}

			game_entities[game_entities.size() -1]->setplayer(game_entities[0]);

			game_entities[game_entities.size() -1]->Init("WOOD", entity_name, entity_type);

			//Second attack
			if(entity_direction.x == 1)
			{
				position.x = shooter->getPosition().x + shooter->GetSprite()->getTextureRect().width/2;
				position.y = (shooter->getCollider()->position.y + shooter->getCollider()->extension.y) - 250 - (projectileHeight/2);
				game_entities.push_back(new Projectile(shooter, entity_type, config_manager, Vector2(1, -0.1), DoubleShot, position));
			}
			else if(entity_direction.x == -1)
			{
				position.x = shooter->getPosition().x;
				position.y = (shooter->getCollider()->position.y + shooter->getCollider()->extension.y) - 250 - (projectileHeight/2);
				game_entities.push_back(new Projectile(shooter, entity_type, config_manager, Vector2(-1, -0.1), DoubleShot, position));
			}

			//What animations
			if(entity_direction.x == 1)
			{
				game_entities[game_entities.size() - 1]->AddAnimation(ATTACKRIGHT, sprite_manager->Load(woodprojectilespritesheet, 4, 4, woodprojectilewidth, woodprojectileheight, woodprojectilewidth*4, woodprojectileheight*1));
				game_entities[game_entities.size() - 1]->AddAnimation(DEATHRIGHT, sprite_manager->Load(woodprojectilespritesheet, 5, 4, woodprojectilewidth, woodprojectileheight, woodprojectilewidth*4, woodprojectileheight*2));
				game_entities[game_entities.size() - 1]->AddAnimation(FADEOUTRIGHT, sprite_manager->Load(woodprojectilespritesheet, 4, 4, woodprojectilewidth, woodprojectileheight, woodprojectilewidth*4, woodprojectileheight*0));
			}
			else if(entity_direction.x == -1)
			{
				game_entities[game_entities.size() - 1]->AddAnimation(ATTACKLEFT, sprite_manager->Load(woodprojectilespritesheet, 4, 4, woodprojectilewidth, woodprojectileheight, woodprojectilewidth*4, woodprojectileheight*5));
				game_entities[game_entities.size() - 1]->AddAnimation(DEATHLEFT, sprite_manager->Load(woodprojectilespritesheet, 5, 4, woodprojectilewidth, woodprojectileheight, woodprojectilewidth*4, woodprojectileheight*6));
				game_entities[game_entities.size() - 1]->AddAnimation(FADEOUTLEFT, sprite_manager->Load(woodprojectilespritesheet, 4, 4, woodprojectilewidth, woodprojectileheight, woodprojectilewidth*4, woodprojectileheight*4));
			}

			game_entities[game_entities.size() -1]->setplayer(game_entities[0]);

			game_entities[game_entities.size() -1]->Init("WOOD", entity_name, entity_type);
		}
		else
		{
			if(entity_direction.x == 1)
			{
				position.x = shooter->getPosition().x + shooter->GetSprite()->getTextureRect().width/2;
				position.y = (shooter->getCollider()->position.y + shooter->getCollider()->extension.y) - 250;
			}
			else if(entity_direction.x == -1)
			{
				position.x = shooter->getPosition().x;
				position.y = (shooter->getCollider()->position.y + shooter->getCollider()->extension.y) - 250;
			}

			game_entities.push_back(new Projectile(shooter, entity_type, config_manager, Vector2(entity_direction.x, 0), DoubleShot, position));
		
			//What animations
			if(entity_direction.x == 1)
			{
				game_entities[game_entities.size() - 1]->AddAnimation(ATTACKRIGHT, sprite_manager->Load(woodprojectilespritesheet, 4, 4, woodprojectilewidth, woodprojectileheight, woodprojectilewidth*4, woodprojectileheight*1));
				game_entities[game_entities.size() - 1]->AddAnimation(DEATHRIGHT, sprite_manager->Load(woodprojectilespritesheet, 5, 4, woodprojectilewidth, woodprojectileheight, woodprojectilewidth*4, woodprojectileheight*2));
				game_entities[game_entities.size() - 1]->AddAnimation(FADEOUTRIGHT, sprite_manager->Load(woodprojectilespritesheet, 4, 4, woodprojectilewidth, woodprojectileheight, woodprojectilewidth*4, woodprojectileheight*0));
			}
			else if(entity_direction.x == -1)
			{
				game_entities[game_entities.size() - 1]->AddAnimation(ATTACKLEFT, sprite_manager->Load(woodprojectilespritesheet, 4, 4, woodprojectilewidth, woodprojectileheight, woodprojectilewidth*4, woodprojectileheight*5));
				game_entities[game_entities.size() - 1]->AddAnimation(DEATHLEFT, sprite_manager->Load(woodprojectilespritesheet, 5, 4, woodprojectilewidth, woodprojectileheight, woodprojectilewidth*4, woodprojectileheight*6));
				game_entities[game_entities.size() - 1]->AddAnimation(FADEOUTLEFT, sprite_manager->Load(woodprojectilespritesheet, 4, 4, woodprojectilewidth, woodprojectileheight, woodprojectilewidth*4, woodprojectileheight*4));
			}

			game_entities[game_entities.size() -1]->setplayer(game_entities[0]);

			game_entities[game_entities.size() -1]->Init("WOOD", entity_name, entity_type);
		}
		break;
	}

}

void EntityManager::AttachWall(Vector2 position, int width, int height, Type wall_type)
{
	game_entities.push_back(new Wall(position, width, height));

	switch (wall_type)
	{
	case FIRE:
		game_entities[game_entities.size() - 1]->AddAnimation(IDLELEFT, sprite_manager->Load("WallPlaceHolder.png", 1, 1, 210, 1000, 0, 0));
		game_entities[game_entities.size() - 1]->Init("FIREWALL", WALL, FIRE);
		break;
	case WATER:
		break;
	case WOOD:
		break;
	}
}

void EntityManager::AttachLostSoul(Alignment entity_name, Entity* enemydropping, int width, int height, Type entity_type, Vector2 entity_position)
{

	game_entities.push_back(new LostSoulObject(enemydropping, entity_position, config_manager));

	game_entities[game_entities.size() - 1]->AddAnimation(IDLELEFT, sprite_manager->Load(lostsoulspritesheet, 7, 4, lostsoulwidth, lostsoulheight, lostsoulwidth*0, lostsoulheight*0));
	game_entities[game_entities.size()-1]->Init("Lost soul", entity_name, entity_type);

}

void EntityManager::AttachAltar(Alignment entity_name, Type entity_type, Vector2 entity_position)
{

	game_entities.push_back(new AltarObject(entity_position, config_manager));

	game_entities[game_entities.size()-1]->AddAnimation(IDLELEFT, sprite_manager->Load("altarspritesheet_small2.png", 21, 6, 270, 364, 0, 0));
	game_entities[game_entities.size()-1]->Init("Altar", entity_name, entity_type);

}

void EntityManager::AttachStaticObject(ConfigManager* ConfigMgr, std::string Object)
{
	//Position
	Vector2 ObjectPosition;
	ObjectPosition.x = ConfigMgr->ReadFloat(Object + "PosX");
	ObjectPosition.y = ConfigMgr->ReadFloat(Object + "PosY");

	//Animation/Sprite
	std::string ObjectSpritesheet = ConfigMgr->GetValueFromKey(Object + "Spritesheet");
	int NumberOfFrames = ConfigMgr->ReadInt(Object + "NumberOfFrames");
	int NumberOfColums = ConfigMgr->ReadInt(Object + "NumberOfColumns");
	int SpriteWidth = ConfigMgr->ReadInt(Object + "SpriteWidth");
	int SpriteHeight = ConfigMgr->ReadInt(Object + "SpriteHeight");

	game_entities.push_back(new StaticObject(ConfigMgr, ObjectPosition, Object));

	//Set the Animation
	if(ObjectSpritesheet != "-")
		game_entities[game_entities.size() - 1]->AddAnimation(IDLELEFT, sprite_manager->Load(ObjectSpritesheet, NumberOfFrames, NumberOfColums, SpriteWidth, SpriteHeight, 0, 0));

	game_entities[game_entities.size() - 1]->Init("Static Object", STATICOBJECT, NONE);
}

void EntityManager::Cleanup()
{
	for(int i = 0; i < game_entities.size(); i ++)
	{
		delete game_entities[i];
		game_entities[i] = nullptr;
		game_entities.erase(game_entities.begin() + i);
	}

	//delete enemy wave spawner:
	if (waves != nullptr){
		delete waves;
		waves = nullptr;
	}

	if(sprite_manager != nullptr)
		sprite_manager = nullptr;

	if(sound_manager != nullptr)
		sound_manager = nullptr;

	if(config_manager != nullptr)
	{
		delete config_manager;
		config_manager = nullptr;
	}
}

void EntityManager::Update(float deltatime)
{
	int count = 0;
	for(int i = 0; i < (game_entities.size()); i++)
	{
		game_entities[i]->setplayer(game_entities[0]);
		game_entities[i]->Update(deltatime);

		//iterate through the collisionmap
		for(int j = i + 1; j < game_entities.size(); j++)
		{
			if(game_entities[i]->hasCollider() && game_entities[j]->hasCollider())
			{
				count ++;
				auto it = CollisionMap.find(std::pair<Alignment, Alignment>(game_entities[i]->getAlignment(), game_entities[j]->getAlignment()));

				std::map<std::pair<Alignment, Alignment>, int>::iterator reverse_it = CollisionMap.find(std::pair<Alignment, Alignment>(game_entities[j]->getAlignment(), game_entities[i]->getAlignment()));

				if(it != CollisionMap.end())
				{
					Vector2 offset = Vector2(0.1f, 0.1f);
					if(game_entities[i]->getCollider()->Overlap(*game_entities[j]->getCollider(), offset))
					{
						if(game_entities[i]->CanCollide() && game_entities[j]->CanCollide())
						{
 							game_entities[i]->OnCollision(game_entities[j],game_entities[j]->getType(), offset, game_entities[j]->getAlignment());
							game_entities[j]->OnCollision(game_entities[i],game_entities[i]->getType(), offset, game_entities[i]->getAlignment());
						}
					}
				}
				else if(reverse_it != CollisionMap.end())
				{
					Vector2 offset = Vector2(0.1f, 0.1f);
					if(game_entities[i]->getCollider()->Overlap(*game_entities[j]->getCollider(), offset))
					{
						if(game_entities[i]->CanCollide() && game_entities[j]->CanCollide())
						{
							game_entities[i]->OnCollision(game_entities[j],game_entities[j]->getType(), offset, game_entities[j]->getAlignment());
							game_entities[j]->OnCollision(game_entities[i],game_entities[i]->getType(), offset, game_entities[i]->getAlignment());
						}
					}
				}
			} //has collider
		} //end of for loop

		//Player associated actions
		if(game_entities[i]->getAlignment() == PLAYER)
		{
			waves->SpawnTimerAlarm(game_entities[i]->getPosition().x);
			//create projectiles
			if(game_entities[i]->getShootDelay() == 0.001f && game_entities[i]->CreateProjectile())
			{
				AttachProjectile(FRIENDBULLET, game_entities[i], 47, 37, game_entities[i]->getType(), game_entities[i]->getDirection(), game_entities[i]->GetDoubleShot());
			}
		}

		//enemy associated actions
		else if(game_entities[i]->getAlignment() == FIREFOE || game_entities[i]->getAlignment() == WATERFOE || game_entities[i]->getAlignment() == WOODFOE)
		{
			for (int j=0; j<game_entities.size(); j++)
			{
				if(i!=j && game_entities[j]->getAlignment() == FIREFOE || game_entities[j]->getAlignment() == WATERFOE || game_entities[j]->getAlignment() == WOODFOE)
				{
					game_entities[i]->SetPositions(game_entities[j]->getPosition());
				}
			}

			game_entities[i]->DontStack();
			game_entities[i]->ClearPositions();

			if(game_entities[i]->getShootDelay() == 0.001f && game_entities[i]->CreateProjectile())
			{
				switch (game_entities[i]->getAlignment())
				{
				case FIREFOE:
					AttachProjectile(FIREFOEBULLET, game_entities[i], 47, 37, game_entities[i]->getType(), game_entities[i]->getDirection(), false);
					break;
				case WATERFOE:
					AttachProjectile(WATERFOEBULLET, game_entities[i], 47, 37, game_entities[i]->getType(), game_entities[i]->getDirection(), false);
					break;
				case WOODFOE:
					AttachProjectile(WOODFOEBULLET, game_entities[i], 47, 37, game_entities[i]->getType(), game_entities[i]->getDirection(), false);
					break;
				}
			}
			if(game_entities[i]->GetLostSoul())
			{
				AttachLostSoul(LOSTSOUL, game_entities[i], 100, 100, game_entities[i]->getType(), game_entities[i]->getPosition());
			}
		}
	}

	for(int i = 0; i < game_entities.size(); i++)
	{
		if(game_entities[i]->IsFlaggedForDeath())
		{
			game_entities[i]->Cleanup();
			delete game_entities[i];
			game_entities[i] = nullptr;
			game_entities.erase(game_entities.begin() + i);

			if(i == 0)
			{
				GAMEOVER = true;
			}
		}
	}
}

bool EntityManager::SwitchState()
{
	return GAMEOVER;
}