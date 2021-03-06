//EntityManager.cpp

#include "stdafx.h"

#include "EntityManager.h"


EntityManager::EntityManager()
{

}

EntityManager::EntityManager(SpriteManager* sprite_mgr, SoundManager* sound_mgr)
{
	sprite_manager = sprite_mgr;
	sound_manager = sound_mgr;
	config_manager = new ConfigManager;
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
	config_manager->ReadFile("Altar.txt");

	//Spritesheet width and height
	playerheight = 210;
	playerwidth = 210;

	fireprojectileheight = 85;
	fireprojectilewidth = 85;
	waterprojectileheight = 85;
	waterprojectilewidth = 85;
	woodprojectileheight = 85;
	woodprojectilewidth = 85;

	fireheight = 210;
	firewidth = 210;
	waterheight = 315;
	waterwidth = 315;
	woodheight = 405;
	woodwidth = 495;

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

		game_entities[game_entities.size() - 1]->AddAnimation(IDLERIGHT, sprite_manager->Load("MC SPRITESHEET 210p.png", 7, 4, playerwidth, playerheight, 0, 0));
		game_entities[game_entities.size() - 1]->AddAnimation(IDLELEFT, sprite_manager->Load("MC SPRITESHEET 210p.png", 7, 4, playerwidth, playerheight, 0, 2520));
		game_entities[game_entities.size() - 1]->AddAnimation(ATTACKRIGHT, sprite_manager->Load("MC SPRITESHEET 210p.png", 5, 4, playerwidth, playerheight, 0, 840));
		game_entities[game_entities.size() - 1]->AddAnimation(ATTACKLEFT, sprite_manager->Load("MC SPRITESHEET 210p.png", 5, 4, playerwidth, playerheight, 0, 3360));
		game_entities[game_entities.size() - 1]->AddAnimation(WALKLEFT, sprite_manager->Load("MC SPRITESHEET 210p.png", 8, 4, playerwidth, playerheight, 0, 2940));
		game_entities[game_entities.size() - 1]->AddAnimation(WALKRIGHT, sprite_manager->Load("MC SPRITESHEET 210p.png", 8, 4, playerwidth, playerheight, 0, 420));
		game_entities[game_entities.size() - 1]->AddAnimation(DEATHLEFT, sprite_manager->Load("MC SPRITESHEET 210p.png", 22, 4, playerwidth, playerheight, 0, 3780));
		game_entities[game_entities.size() - 1]->AddAnimation(DEATHRIGHT, sprite_manager->Load("MC SPRITESHEET 210p.png", 22, 4, playerwidth, playerheight, 0, 1260));
		//sounds
		game_entities[game_entities.size() - 1]->AddSounds(sound_manager);

		game_entities[game_entities.size() - 1]->Init("Player", PLAYER, FIRE);
		break;
	case WATERFOE:
		game_entities.push_back(new WaterEnemyObject(config_manager, position));

		//add animations
		//left
		game_entities[game_entities.size() - 1]->AddAnimation(IDLELEFT, sprite_manager->Load("WATER SPRITESHEET 315p.png", 5, 4, waterwidth, waterheight, 0, 0));
		game_entities[game_entities.size() - 1]->AddAnimation(ATTACKLEFT, sprite_manager->Load("WATER SPRITESHEET 315p.png", 6, 4, waterwidth, waterheight, 0, 4*waterheight));
		game_entities[game_entities.size() - 1]->AddAnimation(DEATHLEFT, sprite_manager->Load("WATER SPRITESHEET 315p.png", 8, 4, waterwidth, waterheight, 0, 6*waterheight));

		//right
		game_entities[game_entities.size() - 1]->AddAnimation(IDLERIGHT, sprite_manager->Load("WATER SPRITESHEET 315p.png", 5, 4, waterwidth, waterheight, 0, 8*waterheight));
		game_entities[game_entities.size() - 1]->AddAnimation(ATTACKRIGHT, sprite_manager->Load("WATER SPRITESHEET 315p.png", 6, 4, waterwidth, waterheight, 0, 12*waterheight));
		game_entities[game_entities.size() - 1]->AddAnimation(DEATHRIGHT, sprite_manager->Load("WATER SPRITESHEET 315p.png", 8, 4, waterwidth, waterheight, 0, 14*waterheight));

		game_entities[game_entities.size()-1]->Init("Water enemy", entity_name, type);

		game_entities[game_entities.size()-1]->setplayer(game_entities[0]);
		break;
	case FIREFOE:
		game_entities.push_back(new FireEnemyObject(config_manager, position));
		//left
		game_entities[game_entities.size()-1]->AddAnimation(IDLELEFT, sprite_manager->Load("FIRE SPRITESHEET 210p.png", 4, 4, firewidth, fireheight, 0, 0));
		game_entities[game_entities.size()-1]->AddAnimation(WALKLEFT, sprite_manager->Load("FIRE SPRITESHEET 210p.png", 4, 4, firewidth, fireheight, 0, 210));
		game_entities[game_entities.size()-1]->AddAnimation(ATTACKLEFT, sprite_manager->Load("FIRE SPRITESHEET 210p.png", 6, 4, firewidth, fireheight, 0, 420));
		game_entities[game_entities.size()-1]->AddAnimation(DEATHLEFT, sprite_manager->Load("FIRE SPRITESHEET 210p.png", 7, 4, firewidth, fireheight, 0, 840));

		//right
		game_entities[game_entities.size()-1]->AddAnimation(IDLERIGHT, sprite_manager->Load("FIRE SPRITESHEET 210p.png", 4, 4, firewidth, fireheight, 0, 1260));
		game_entities[game_entities.size()-1]->AddAnimation(WALKRIGHT, sprite_manager->Load("FIRE SPRITESHEET 210p.png", 4, 4, firewidth, fireheight, 0, 1470));
		game_entities[game_entities.size()-1]->AddAnimation(ATTACKRIGHT, sprite_manager->Load("FIRE SPRITESHEET 210p.png", 6, 4, firewidth, fireheight, 0, 1680));
		game_entities[game_entities.size()-1]->AddAnimation(DEATHRIGHT, sprite_manager->Load("FIRE SPRITESHEET 210p.png", 7, 4, firewidth, fireheight, 0, 2100));

		game_entities[game_entities.size()-1]->Init("Fire enemy", entity_name, type);

		game_entities[game_entities.size()-1]->setplayer(game_entities[0]);
		break;
	case WOODFOE:
		game_entities.push_back(new WoodEnemyObject(config_manager, position));
		//left
		game_entities[game_entities.size()-1]->AddAnimation(IDLELEFT, sprite_manager->Load("WOOD SPRITESHEET 495x405p.png", 6, 9, woodwidth, woodheight, 0, 0*woodheight));
		game_entities[game_entities.size()-1]->AddAnimation(WALKLEFT, sprite_manager->Load("WOOD SPRITESHEET 495x405p.png", 8, 9, woodwidth, woodheight, 0, 1*woodheight));
		game_entities[game_entities.size()-1]->AddAnimation(ATTACKLEFT, sprite_manager->Load("WOOD SPRITESHEET 495x405p.png", 9, 9, woodwidth, woodheight, 0, 2*woodheight));
		game_entities[game_entities.size()-1]->AddAnimation(DEATHLEFT, sprite_manager->Load("WOOD SPRITESHEET 495x405p.png", 9, 9, woodwidth, woodheight, 0, 3*woodheight));

		//right
		game_entities[game_entities.size()-1]->AddAnimation(IDLERIGHT, sprite_manager->Load("WOOD SPRITESHEET 495x405p.png", 6, 9, woodwidth, woodheight, 0, 4*woodheight));
		game_entities[game_entities.size()-1]->AddAnimation(WALKRIGHT, sprite_manager->Load("WOOD SPRITESHEET 495x405p.png", 8, 9, woodwidth, woodheight, 0, 5*woodheight));
		game_entities[game_entities.size()-1]->AddAnimation(ATTACKRIGHT, sprite_manager->Load("WOOD SPRITESHEET 495x405p.png", 9, 9, woodwidth, woodheight, 0, 6*woodheight));
		game_entities[game_entities.size()-1]->AddAnimation(DEATHRIGHT, sprite_manager->Load("WOOD SPRITESHEET 495x405p.png", 9, 9, woodwidth, woodheight, 0, 7*woodheight));

		game_entities[game_entities.size()-1]->Init("Wood enemy", entity_name, type);

		game_entities[game_entities.size()-1]->setplayer(game_entities[0]);
		break;
	}
}

void EntityManager::DetachEntity(int entity_index)
{
	/*
	Delete the entity, appropriate to the string that followed
	*/
}

void EntityManager::AttachProjectile(Alignment entity_name, Entity* shooter, int width, int height, Type entity_type, Vector2 entity_direction)
{
	switch (entity_type)
	{
	case FIRE:
		game_entities.push_back(new Projectile(shooter, config_manager, entity_direction));

		//What animations
		if(entity_direction.x == 1)
		{
			game_entities[game_entities.size() - 1]->AddAnimation(ATTACKRIGHT, sprite_manager->Load("PROJECTILE SPRITESHEET 85p.png", 4, 4, 85, 85, 0, 0));
			game_entities[game_entities.size() - 1]->AddAnimation(DEATHRIGHT, sprite_manager->Load("PROJECTILE SPRITESHEET 85p.png", 5, 4, 85, 85, 0, 85));
		}
		else if(entity_direction.x == -1)
		{
			game_entities[game_entities.size() - 1]->AddAnimation(ATTACKLEFT, sprite_manager->Load("PROJECTILE SPRITESHEET 85p.png", 4, 4, 85, 85, 0, 255));
			game_entities[game_entities.size() - 1]->AddAnimation(DEATHLEFT, sprite_manager->Load("PROJECTILE SPRITESHEET 85p.png", 5, 4, 85, 85, 0, 340));
		}

		game_entities[game_entities.size() -1]->Init("FIRE", entity_name, entity_type);
		break;

	case WATER:
		game_entities.push_back(new Projectile(shooter, config_manager, entity_direction));

		//What animations
		if(entity_direction.x == 1)
		{
			game_entities[game_entities.size() - 1]->AddAnimation(ATTACKRIGHT, sprite_manager->Load("PROJECTILE SPRITESHEET 85p.png", 4, 4, 85, 85, 0, 510));
			game_entities[game_entities.size() - 1]->AddAnimation(DEATHRIGHT, sprite_manager->Load("PROJECTILE SPRITESHEET 85p.png", 5, 4, 85, 85, 0, 595));
		}
		else if(entity_direction.x == -1)
		{
			game_entities[game_entities.size() - 1]->AddAnimation(ATTACKLEFT, sprite_manager->Load("PROJECTILE SPRITESHEET 85p.png", 4, 4, 85, 85, 0, 765));
			game_entities[game_entities.size() - 1]->AddAnimation(DEATHLEFT, sprite_manager->Load("PROJECTILE SPRITESHEET 85p.png", 5, 4, 85, 85, 0, 850));
		}

		game_entities[game_entities.size() -1]->Init("WATER", entity_name, entity_type);
		break;

	case WOOD:

		game_entities.push_back(new Projectile(shooter, config_manager, entity_direction));
		
		//What animations
		if(entity_direction.x == 1)
		{
			game_entities[game_entities.size() - 1]->AddAnimation(ATTACKRIGHT, sprite_manager->Load("PROJECTILE SPRITESHEET 85p.png", 4, 4, 85, 85, 0, 1020));
			game_entities[game_entities.size() - 1]->AddAnimation(DEATHRIGHT, sprite_manager->Load("PROJECTILE SPRITESHEET 85p.png", 5, 4, 85, 85, 0, 1105));
		}
		else if(entity_direction.x == -1)
		{
			game_entities[game_entities.size() - 1]->AddAnimation(ATTACKLEFT, sprite_manager->Load("PROJECTILE SPRITESHEET 85p.png", 4, 4, 85, 85, 0, 1275));
			game_entities[game_entities.size() - 1]->AddAnimation(DEATHLEFT, sprite_manager->Load("PROJECTILE SPRITESHEET 85p.png", 5, 4, 85, 85, 0, 1360));
		}

		game_entities[game_entities.size() -1]->Init("WOOD", entity_name, entity_type);
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

	game_entities[game_entities.size() - 1]->AddAnimation(IDLELEFT, sprite_manager->Load("Lost Souls Spritesheet.png", 7, 4, 100, 100, 0, 0));
	game_entities[game_entities.size()-1]->Init("Lost soul", entity_name, entity_type);

}

void EntityManager::AttachAltar(Alignment entity_name, int width, int height, Type entity_type, Vector2 entity_position)
{

	game_entities.push_back(new AltarObject(entity_position, config_manager));

	game_entities[game_entities.size()-1]->AddAnimation(IDLELEFT, sprite_manager->Load("altarspritesheet_small.png", 21, 6, 225, 312, 0, 0));
	game_entities[game_entities.size()-1]->Init("Altar", entity_name, entity_type);

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
				AttachProjectile(FRIENDBULLET, game_entities[i], 47, 37, game_entities[i]->getType(), game_entities[i]->getDirection());
			}
		}

		//Fireenemy associated actions
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
					AttachProjectile(FIREFOEBULLET, game_entities[i], 47, 37, game_entities[i]->getType(), game_entities[i]->getDirection());
					break;
				case WATERFOE:
					AttachProjectile(WATERFOEBULLET, game_entities[i], 47, 37, game_entities[i]->getType(), game_entities[i]->getDirection());
					break;
				case WOODFOE:
					AttachProjectile(WOODFOEBULLET, game_entities[i], 47, 37, game_entities[i]->getType(), game_entities[i]->getDirection());
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
		}
	}
}