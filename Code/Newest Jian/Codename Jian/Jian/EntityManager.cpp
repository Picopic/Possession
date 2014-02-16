//EntityManager.cpp

#include "stdafx.h"


#include "EntityManager.h"


EntityManager::EntityManager()
{
	
}

EntityManager::EntityManager(SpriteManager* sprite_mgr)
{
	sprite_manager = sprite_mgr;
}

EntityManager::~EntityManager()
{

}

void EntityManager::Init()
{
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (PLAYER, WATERFOE), 0));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (PLAYER, WOODFOE), 1));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (PLAYER, FIREFOE), 2));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (PLAYER, WATERFOEBULLET), 3));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (PLAYER, WOODFOEBULLET), 4));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (PLAYER, FIREFOEBULLET), 5));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (WATERFOE, PLAYER), 6));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (WATERFOE, FRIENDBULLET), 7));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (WOODFOE, PLAYER), 8));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (WOODFOE, FRIENDBULLET), 9));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (FIREFOE, PLAYER), 10));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (FIREFOE, FRIENDBULLET), 11));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (FRIENDBULLET, WATERFOE), 12));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (FRIENDBULLET, WOODFOE), 13));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (FRIENDBULLET, FIREFOE), 14));

	game_entities.push_back(new PlayerObject(Vector2(400.0f, 0.0f), 210, 210));
	game_entities[game_entities.size() - 1]->AddAnimation(IDLE, sprite_manager->Load("Placeholder Spritesheet MC 210p new.png", 3, 4, 210, 210, 0, 0));
	game_entities[game_entities.size() - 1]->AddAnimation(ATTACKRIGHT, sprite_manager->Load("Placeholder Spritesheet MC 210p new.png", 4, 4, 210, 210, 0, 630));
	game_entities[game_entities.size() - 1]->AddAnimation(WALKLEFT, sprite_manager->Load("Placeholder Spritesheet MC 210p new.png", 4, 4, 210, 210, 0, 210));
	game_entities[game_entities.size() - 1]->AddAnimation(WALKRIGHT, sprite_manager->Load("Placeholder Spritesheet MC 210p new.png", 4, 4, 210, 210, 0, 420));
	game_entities[game_entities.size() - 1]->Init("Player", PLAYER, FIRE);
	game_entities[game_entities.size() - 1]->setDelay(0.4f);
}

void EntityManager::AttachEntity(Alignment entity_name, Vector2 position, int width, int height, Type type)
{
	/*
		create new entity, appropriate to the string that followed
	*/
	switch(entity_name)
	{
	case WATERFOE:
		game_entities.push_back(new WaterEnemyObject(position, width, height));
		game_entities[game_entities.size()-1]->Init("Water enemy", entity_name, type);
		break;
	case FIREFOE:
		game_entities.push_back(new FireEnemyObject(position, width, height));
		game_entities[game_entities.size()-1]->AddAnimation(IDLE, sprite_manager->Load("FIRE SPRITESHEET 210p.png", 4, 4, 210, 210, 0, 0));
		game_entities[game_entities.size()-1]->AddAnimation(DEATH, sprite_manager->Load("FIRE SPRITESHEET 210p.png", 7, 4, 210, 210, 0, 840));
		game_entities[game_entities.size()-1]->Init("Fire enemy", entity_name, type);
		break;
	//case PLAYER:
		//game_entities.push_back(new PlayerObject(position, width, height));
		//game_entities[game_entities.size() - 1]->Init("Player", entity_name, FIRE);
		//break;
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
	switch (entity_name)
	{
	case FRIENDBULLET:
		game_entities.push_back(new Projectile(shooter, width, height, entity_direction));

		//What animations
		if(entity_direction.x == 1)
		{
			game_entities[game_entities.size() - 1]->AddAnimation(ATTACKRIGHT, sprite_manager->Load("Placeholder Projectiles.png", 4, 4, 65, 65, 0, 0));
			game_entities[game_entities.size() - 1]->AddAnimation(DEATH, sprite_manager->Load("Placeholder Projectiles.png", 5, 4, 65, 65, 0, 65));
		}
		else if(entity_direction.x == -1)
		{
			game_entities[game_entities.size() - 1]->AddAnimation(ATTACKLEFT, sprite_manager->Load("Placeholder Projectiles.png", 4, 4, 65, 65, 0, 0));
			game_entities[game_entities.size() - 1]->AddAnimation(DEATH, sprite_manager->Load("Placeholder Projectiles.png", 5, 4, 65, 65, 0, 65));
		}

		game_entities[game_entities.size() -1]->Init("PLAYER BULLET", entity_name, entity_type);
		break;
	case FIREFOEBULLET:
		game_entities.push_back(new Projectile(shooter, width, height, entity_direction));

		if(entity_direction.x == 1)
		{
			game_entities[game_entities.size() - 1]->AddAnimation(ATTACKRIGHT, sprite_manager->Load("Placeholder Projectiles.png", 4, 4, 65, 65, 0, 0));
			game_entities[game_entities.size() - 1]->AddAnimation(DEATH, sprite_manager->Load("Placeholder Projectiles.png", 5, 4, 65, 65, 0, 65));
		}
		else if(entity_direction.x == -1)
		{
			game_entities[game_entities.size() - 1]->AddAnimation(ATTACKLEFT, sprite_manager->Load("Placeholder Projectiles.png", 4, 4, 65, 65, 0, 0));
			game_entities[game_entities.size() - 1]->AddAnimation(DEATH, sprite_manager->Load("Placeholder Projectiles.png", 5, 4, 65, 65, 0, 65));
		}

		game_entities[game_entities.size() -1]->Init("PLAYER BULLET", entity_name, entity_type);
		break;
	case WATERFOEBULLET:
		break;
	case WOODFOEBULLET:
		break;
	}
	
}

void EntityManager::Cleanup()
{
	for(int i = 0; i < game_entities.size(); i ++)
	{
		delete game_entities[i];
		game_entities[i] = nullptr;
		game_entities.erase(game_entities.begin() + i);
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
				if(it != CollisionMap.end())
				{
					Vector2 offset = Vector2(0.1f, 0.1f);
					if(game_entities[i]->getCollider()->Overlap(*game_entities[j]->getCollider(), offset))
					{
						game_entities[i]->OnCollision(game_entities[j]->getType(), offset, game_entities[j]->getAlignment());
						game_entities[j]->OnCollision(game_entities[i]->getType(), offset, game_entities[i]->getAlignment());
					}
				}
			}
		}

		//create projectiles
		if(game_entities[i]->getAlignment() == PLAYER)
		{
			if(game_entities[i]->getShootDelay() == 0.001f && game_entities[i]->CreateProjectile())
			{
				AttachProjectile(FRIENDBULLET, game_entities[i], 10, 10, game_entities[i]->getType(), game_entities[i]->getDirection());
				game_entities.at(i)->resetShootDelay();
			}
		}
		if(game_entities[i]->getAlignment() == FIREFOE)
		{
			if(game_entities[i]->getShootDelay() >= 2.0f && game_entities[i]->CreateProjectile())
			{
				AttachProjectile(FIREFOEBULLET, game_entities[i], 10, 10, game_entities[i]->getType(), game_entities[i]->getDirection()); 
				game_entities.at(i)->resetShootDelay();
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