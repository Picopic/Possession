//HeadsUpDisplay.cpp

#include "stdafx.h"

#include "Enums.h"
#include "Vector2.h"

#include "AnimatedSprite.h"
#include "SpriteManager.h"                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
#include "HeadsUpDisplay.h"
#include "ConfigManager.h"

HeadsUpDisplay::HeadsUpDisplay()
{

}

bool HeadsUpDisplay::Initialise(SpriteManager* sprite_mgr)
{
	m_ConfigManager = new ConfigManager;
	if(!m_ConfigManager->Initialise("../data/Configs/"))
		return false;

	m_ConfigManager->ReadFile("Config.txt");

	//Souls
	SoulWidth = 100;
	SoulHeight = 100;
	SoulXPos = /*m_ConfigManager->ReadInt("WindowWidth")*/ 1920 - SoulWidth;
	SoulYPos = 10;

	//Spritemanagers
	m_SpriteManager = sprite_mgr;

	//Points
	fire = 3;
	water = 3;
	wood = 3;

	//Width & Height of pictures
	sprite_width = 115;
	sprite_height = 115;

	//Symbolpositions
	position[0].x = 20;					//Water
	position[0].y = 10;
	position[1].x = 20 + sprite_width;	//Fire
	position[1].y = 10;
	position[2].x = 20 + 2*sprite_width;//Wood
	position[2].y = 10;

	//Active element
	ActiveElement = FIRE;

	//Number of images
	NumberOfImages = 10;

	//Alive symbols
	for(int i = 0; i < NumberOfImages; i++)
	{
		//Inactive symbols
		InactiveFireSymbols.push_back(sprite_mgr->Load("Elements GUI.png", 10, 10, sprite_width, sprite_height, i*sprite_width, 1*sprite_height));
		InactiveWaterSymbols.push_back(sprite_mgr->Load("Elements GUI.png", 10, 10, sprite_width, sprite_height, i*sprite_width, 3*sprite_height));
		InactiveWoodSymbols.push_back(sprite_mgr->Load("Elements GUI.png", 10, 10, sprite_width, sprite_height, i*sprite_width, 5*sprite_height));

		//Active symbols
		ActiveFireSymbols.push_back(sprite_mgr->Load("Elements GUI.png", 10, 10, sprite_width, sprite_height, i*sprite_width, 0*sprite_height));
		ActiveWaterSymbols.push_back(sprite_mgr->Load("Elements GUI.png", 10, 10, sprite_width, sprite_height, i*sprite_width, 2*sprite_height));
		ActiveWoodSymbols.push_back(sprite_mgr->Load("Elements GUI.png", 10, 10, sprite_width, sprite_height, i*sprite_width, 4*sprite_height));
	}

	//Dead symbols
	DeadFire = sprite_mgr->Load("Elements GUI.png", 10, 10, sprite_width, sprite_height, 0*sprite_width, 6*sprite_height);
	DeadWater = sprite_mgr->Load("Elements GUI.png", 10, 10, sprite_width, sprite_height, 1*sprite_width, 6*sprite_height);
	DeadWood = sprite_mgr->Load("Elements GUI.png", 10, 10, sprite_width, sprite_height, 2*sprite_width, 6*sprite_height);
	deadfire = false;
	deadwater = false;
	deadwood = false;

	return true;
}

void HeadsUpDisplay::Cleanup()
{
	//SpriteManager
	if(m_SpriteManager != nullptr)
		m_SpriteManager = nullptr;
	//Configmanager
	if(m_ConfigManager != nullptr)
	{
		delete m_ConfigManager;
		m_ConfigManager = nullptr;
	}

	//Dead symbols
	if(DeadFire != nullptr)
	{
		delete DeadFire;
		DeadFire = nullptr;
	}
	if(DeadWater != nullptr)
	{
		delete DeadWater;
		DeadWater = nullptr;
	}
	if(DeadWood != nullptr)
	{
		delete DeadWood;
		DeadWood = nullptr;
	}

	for(int i = 0; i < NumberOfImages; i++)
	{
		//Inactive
		if(InactiveFireSymbols[i] != nullptr)
		{
			delete InactiveFireSymbols[i];
			InactiveFireSymbols[i] = nullptr;
		}
		if(InactiveWaterSymbols[i] != nullptr)
		{
			delete InactiveWaterSymbols[i];
			InactiveWaterSymbols[i] = nullptr;
		}
		if(InactiveWoodSymbols[i] != nullptr)
		{
			delete InactiveWoodSymbols[i];
			InactiveWoodSymbols[i] = nullptr;
		}

		//Active
		if(ActiveFireSymbols[i] != nullptr)
		{
			delete ActiveFireSymbols[i];
			ActiveFireSymbols[i] = nullptr;
		}
		if(ActiveWaterSymbols[i] != nullptr)
		{
			delete ActiveWaterSymbols[i];
			ActiveWaterSymbols[i] = nullptr;
		}
		if(ActiveWoodSymbols[i] != nullptr)
		{
			delete ActiveWoodSymbols[i];
			ActiveWoodSymbols[i] = nullptr;
		}
	}

	for(int i = 0; i < Souls.size(); i++)
	{
		if(Souls[i] != nullptr)
		{
			delete Souls[i];
			Souls[i] = nullptr;
		}
	}
}

void HeadsUpDisplay::Update(float deltatime)
{
	if(fire > 0 || water > 0 || wood > 0)
	{
		for(int i = 0; i < Souls.size(); i++)
		{
			//Souls[i]->Update(deltatime);
		}
	
		if(ActiveElement == FIRE)
			ActiveFireSymbols[fire - 1]->getSprite()->setPosition(position[1]);
		else if(fire <= 0)
			DeadFire->getSprite()->setPosition(position[1]);
		else
			InactiveFireSymbols[fire - 1]->getSprite()->setPosition(position[1]);

		if(ActiveElement == WATER)
			ActiveWaterSymbols[water - 1]->getSprite()->setPosition(position[0]);
		else if(water <= 0)
			DeadWater->getSprite()->setPosition(position[0]);
		else
			InactiveWaterSymbols[water - 1]->getSprite()->setPosition(position[0]);

		if(ActiveElement == WOOD)
			ActiveWoodSymbols[wood - 1]->getSprite()->setPosition(position[2]);
		else if(wood <= 0)
			DeadWood->getSprite()->setPosition(position[2]);
		else
			InactiveWoodSymbols[wood - 1]->getSprite()->setPosition(position[2]);
	}	
}

void HeadsUpDisplay::Restart()
{
	fire = 3;
	water = 3;
	wood = 3;

	//Reset:a souls
	for(int i = 0; i < Souls.size(); i++)
	{
		if(Souls[i] != nullptr)
		{
			delete Souls[i];
			Souls[i] = nullptr;
		}
	}

	Souls.clear();
}

void HeadsUpDisplay::DrawHUD(sf::RenderWindow* window)
{	
	if(fire > 0 || water > 0 || wood > 0)
	{
		//DrawSouls
		for(int i = 0; i < Souls.size(); i++)
		{
			window->draw(*Souls[i]->getSprite());
		}

		//Draw fire
		if(fire > 0 && ActiveElement == FIRE)
			window->draw(*ActiveFireSymbols[fire - 1]->getSprite());
		else if(fire > 0)
			window->draw(*InactiveFireSymbols[fire - 1]->getSprite());
		else
			window->draw(*DeadFire->getSprite());

		//Draw water
		if(water > 0 && ActiveElement == WATER)
			window->draw(*ActiveWaterSymbols[water - 1]->getSprite());
		else if(water > 0)
			window->draw(*InactiveWaterSymbols[water - 1]->getSprite());
		else
			window->draw(*DeadWater->getSprite());

		//Draw wood
		if(wood > 0 && ActiveElement == WOOD)
			window->draw(*ActiveWoodSymbols[wood - 1]->getSprite());
		else if(wood > 0)
			window->draw(*InactiveWoodSymbols[wood - 1]->getSprite());
		else
			window->draw(*DeadWood->getSprite());
	}
}

void HeadsUpDisplay::Move(float x, float y)
{
	//Souls
	SoulXPos += x;
	SoulYPos += y;
	for(int i = 0; i < Souls.size(); i++)
	{
		Souls[i]->getSprite()->move(x, y);
	}

	//Positions movement
	for(int i = 0; i < 3; i++)
	{
		position[i].x += x;
		position[i].y += y;
	}

	
}

void HeadsUpDisplay::MoveIndicator(Type type)
{
	ActiveElement = type;
}

void HeadsUpDisplay::AddElements(sf::Vector3i elements)
{
	//fire
	if(fire + elements.x > 10)
		fire = 10;
	else
		fire += elements.x;
	//water
	if(water + elements.y > 10)
		water = 10;
	else
		water += elements.y;
	//wood
	if(wood + elements.z > 10)
		wood = 10;
	else
		wood += elements.z;

	if(fire > 0)
		deadfire = false;
	if(water > 0)
		deadwater = false;
	if(wood > 0)
		deadwood = false;
}

void HeadsUpDisplay::DeleteElements(sf::Vector3i elements)
{
	//fire
	if(fire - elements.x < 0)
	{
		fire = 0;
		deadfire = true;
	}
	else
		fire -= elements.x;
	//water
	if(water - elements.y < 0)
	{
		water = 0;
		deadwater = true;
	}
	else
		water -= elements.y;
	//wood
	if(wood - elements.z < 0)
	{
		wood = 0;
		deadwood = true;
	}
	else
		wood -= elements.z;
}

void HeadsUpDisplay::AddSoul()
{
	Souls.push_back(m_SpriteManager->Load("Lost souls icon.png", 7, 4, SoulWidth, SoulHeight, 0, 0));
	Souls[Souls.size() - 1]->getSprite()->setPosition(SoulXPos, SoulYPos);
	SoulXPos -= SoulWidth;
}

void HeadsUpDisplay::DeleteSoul()
{
	if(Souls[Souls.size() - 1] != nullptr)
	{
		delete Souls[Souls.size() - 1];
		Souls[Souls.size() - 1] = nullptr;
		Souls.erase(Souls.begin() + (Souls.size() - 1));

		SoulXPos += SoulWidth;
	}
}