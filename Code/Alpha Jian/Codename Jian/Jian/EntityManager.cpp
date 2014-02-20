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
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (PLAYER, LOSTSOUL), 6));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (WATERFOE, PLAYER), 7));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (WATERFOE, FRIENDBULLET), 8));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (WOODFOE, PLAYER), 9));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (WOODFOE, FRIENDBULLET), 10));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (FIREFOE, PLAYER), 11));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (FIREFOE, FRIENDBULLET), 12));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (FRIENDBULLET, WATERFOE), 13));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (FRIENDBULLET, WOODFOE), 14));
	CollisionMap.insert(std::pair<std::pair<Alignment, Alignment>, int>(std::pair<Alignment, Alignment> (FRIENDBULLET, FIREFOE), 15));
}

void EntityManager::AttachEntity(Alignment entity_name, Vector2 position, int width, int height, Type type)
{
	/*
		create new entity, appropriate to the string that followed
	*/
	switch(entity_name)
	{
	case PLAYER:
		game_entities.push_back(new PlayerObject(position, width, height));
		game_entities[game_entities.size() - 1]->AddAnimation(IDLERIGHT, sprite_manager->Load("MC SPRITESHEET 210p.png", 7, 4, 210, 210, 0, 0));
		game_entities[game_entities.size() - 1]->AddAnimation(IDLELEFT, sprite_manager->Load("MC SPRITESHEET 210p.png", 7, 4, 210, 210, 0, 1680));
		game_entities[game_entities.size() - 1]->AddAnimation(ATTACKRIGHT, sprite_manager->Load("MC SPRITESHEET 210p.png", 5, 4, 210, 210, 0, 840));
		game_entities[game_entities.size() - 1]->AddAnimation(ATTACKLEFT, sprite_manager->Load("MC SPRITESHEET 210p.png", 5, 4, 210, 210, 0, 2520));
		game_entities[game_entities.size() - 1]->AddAnimation(WALKLEFT, sprite_manager->Load("MC SPRITESHEET 210p.png", 8, 4, 210, 210, 0, 2100));
		game_entities[game_entities.size() - 1]->AddAnimation(WALKRIGHT, sprite_manager->Load("MC SPRITESHEET 210p.png", 8, 4, 210, 210, 0, 420));
		game_entities[game_entities.size() - 1]->AddAnimation(DEATHLEFT, sprite_manager->Load("MC SPRITESHEET 210p.png", 7, 4, 210, 210, 0, 2940));
		game_entities[game_entities.size() - 1]->AddAnimation(DEATHRIGHT, sprite_manager->Load("MC SPRITESHEET 210p.png", 7, 4, 210, 210, 0, 1260));
		game_entities[game_entities.size() - 1]->Init("Player", PLAYER, FIRE);
		game_entities[game_entities.size() - 1]->setDelay(0.4f);
		break;
	case WATERFOE:
		game_entities.push_back(new WaterEnemyObject(position, width, height));
		game_entities[game_entities.size()-1]->Init("Water enemy", entity_name, type);
		break;
	case FIREFOE:
		game_entities.push_back(new FireEnemyObject(position, width, height));
		game_entities[game_entities.size() -1]->setDelay(3.0f);
		//left
		game_entities[game_entities.size()-1]->AddAnimation(IDLELEFT, sprite_manager->Load("FIRE SPRITESHEET 210p.png", 4, 4, 210, 210, 0, 0));
		game_entities[game_entities.size()-1]->AddAnimation(WALKLEFT, sprite_manager->Load("FIRE SPRITESHEET 210p.png", 4, 4, 210, 210, 0, 210));
		game_entities[game_entities.size()-1]->AddAnimation(ATTACKLEFT, sprite_manager->Load("FIRE SPRITESHEET 210p.png", 6, 4, 210, 210, 0, 420));
		game_entities[game_entities.size()-1]->AddAnimation(DEATHLEFT, sprite_manager->Load("FIRE SPRITESHEET 210p.png", 7, 4, 210, 210, 0, 840));
		
		//right
		game_entities[game_entities.size()-1]->AddAnimation(IDLERIGHT, sprite_manager->Load("FIRE SPRITESHEET 210p.png", 4, 4, 210, 210, 0, 1260));
		game_entities[game_entities.size()-1]->AddAnimation(WALKRIGHT, sprite_manager->Load("FIRE SPRITESHEET 210p.png", 4, 4, 210, 210, 0, 1470));
		game_entities[game_entities.size()-1]->AddAnimation(ATTACKRIGHT, sprite_manager->Load("FIRE SPRITESHEET 210p.png", 6, 4, 210, 210, 0, 1680));
		game_entities[game_entities.size()-1]->AddAnimation(DEATHRIGHT, sprite_manager->Load("FIRE SPRITESHEET 210p.png", 7, 4, 210, 210, 0, 2100));

		game_entities[game_entities.size()-1]->Init("Fire enemy", entity_name, type);
		break;

	case LOSTSOUL:
		game_entities.push_back(new LostSoulObject(position, width, height));
		game_entities[game_entities.size() - 1]->AddAnimation(IDLELEFT, sprite_manager->Load("temporarlostsoul.png", 1, 1, 85, 85, 0, 0));
		game_entities[game_entities.size()-1]->Init("Lost soul", entity_name, type);
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
		game_entities.push_back(new Projectile(shooter, width, height, entity_direction));

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
		game_entities.push_back(new Projectile(shooter, width, height, entity_direction));

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
		game_entities.push_back(new Projectile(shooter, width, height, entity_direction));
		
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
						if(game_entities[i]->CanCollide() && game_entities[j]->CanCollide())
						{
							game_entities[i]->OnCollision(game_entities[j]->getType(), offset, game_entities[j]->getAlignment());
							game_entities[j]->OnCollision(game_entities[i]->getType(), offset, game_entities[i]->getAlignment());
						}
					}
				}
			}
		}

		//create projectiles
		if(game_entities[i]->getAlignment() == PLAYER)
		{
			if(game_entities[i]->getShootDelay() == 0.001f && game_entities[i]->CreateProjectile())
			{
				AttachProjectile(FRIENDBULLET, game_entities[i], 65, 65, game_entities[i]->getType(), game_entities[i]->getDirection());
			}
		}
		else if(game_entities[i]->getAlignment() == FIREFOE)
		{
			if(game_entities[i]->getShootDelay() == 0.001f && game_entities[i]->CreateProjectile())
			{
				AttachProjectile(FIREFOEBULLET, game_entities[i], 65, 65, game_entities[i]->getType(), game_entities[i]->getDirection());
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

	if(game_entities.size() == 1)
	{
		AttachEntity(FIREFOE, Vector2(800, 200), 100, 80, FIRE);
		AttachEntity(LOSTSOUL, Vector2(800, 500), 100, 80, FIRE);
	}
}