//HeadsUpDisplay.cpp

#include "stdafx.h"

#include "Enums.h"

#include "AnimatedSprite.h"
#include "SpriteManager.h"
#include "HeadsUpDisplay.h"

HeadsUpDisplay::HeadsUpDisplay()
{
}

HeadsUpDisplay::~HeadsUpDisplay()
{
}

bool HeadsUpDisplay::Initialise(SpriteManager* sprite_mgr)
{
	hud_arrow = sprite_mgr->Load("Placeholder HUD .png", 1, 1, 65, 65, 195, 0);
	if(hud_arrow == nullptr)	return false;

	symbols.push_back(sprite_mgr->Load("Placeholder HUD .png", 1, 1, 65, 65, 0, 0));
	if(symbols[symbols.size() - 1] == nullptr) return false;
	symbols.push_back(sprite_mgr->Load("Placeholder HUD .png", 1, 1, 65, 65, 65, 0));
	if(symbols[symbols.size() - 1] == nullptr) return false;
	symbols.push_back(sprite_mgr->Load("Placeholder HUD .png", 1, 1, 65, 65, 130, 0));
	if(symbols[symbols.size() - 1] == nullptr) return false;

	fire_template = sprite_mgr->Load("Placeholder HUD .png", 1, 1, 65, 65, 65, 65);
	if(fire_template == nullptr) return false;
	water_template = sprite_mgr->Load("Placeholder HUD .png", 1, 1, 65, 65, 0, 65);
	if(water_template == nullptr) return false;
	wood_template = sprite_mgr->Load("Placeholder HUD .png", 1, 1, 65, 65, 130, 65);
	if(wood_template == nullptr) return false;


	//Give them their positions
	hud_arrow->getSprite()->setPosition(20, 80);

	for(int i = 0; i < symbols.size(); i++)
	{
		symbols[i]->getSprite()->setPosition(80, 80 + (i * 65));
	}

	Update(0);

	return true;
}

void HeadsUpDisplay::Cleanup()
{
	if(hud_arrow != nullptr)
	{
		delete hud_arrow;
		hud_arrow = nullptr;
	}
	if(fire_template != nullptr)
	{
		delete fire_template;
		fire_template = nullptr;
	}
	if(water_template != nullptr)
	{
		delete water_template;
		water_template = nullptr;
	}
	if(wood_template != nullptr)
	{
		delete wood_template;
		wood_template = nullptr;
	}

	//symbols
	for(int i = 0; i < symbols.size(); i++)
	{
		delete symbols[i];
		symbols[i] = nullptr;
	}

	//delete the points
	for(int i = 0; i < fire_points.size(); i++)
	{
		delete fire_points[i];
		fire_points[i] = nullptr;
	}
	for(int i = 0; i < water_points.size(); i++)
	{
		delete water_points[i];
		water_points[i] = nullptr;
	}
	for(int i = 0; i < wood_points.size(); i++)
	{
		delete wood_points[i];
		wood_points[i] = nullptr;
	}
}

void HeadsUpDisplay::DrawHUD(sf::RenderWindow* window)
{
	//arrow
	window->draw(*hud_arrow->getSprite());
	
	//symbols
	for(int i = 0; i < symbols.size(); i++)
	{
		window->draw(*symbols[i]->getSprite());
	}
	//fire
	for(int i = 0; i < fire_points.size(); i++)
	{
		window->draw(*fire_points[i]->getSprite());
	}
	//water
	for(int i = 0; i < water_points.size(); i++)
	{
		window->draw(*water_points[i]->getSprite());
	}
	//wood
	for(int i = 0; i < wood_points.size(); i++)
	{
		window->draw(*wood_points[i]->getSprite());
	}
}

void HeadsUpDisplay::Update(float deltatime)
{
	//arrow
	hud_arrow->Update(deltatime);
	
	//symbols
	for(int i = 0; i < symbols.size(); i++)
	{
		symbols[i]->Update(deltatime);
	}
	//fire
	for(int i = 0; i < fire_points.size(); i++)
	{
		fire_points[i]->Update(deltatime);
	}
	//water
	for(int i = 0; i < water_points.size(); i++)
	{
		water_points[i]->Update(deltatime);
	}
	//wood
	for(int i = 0; i < wood_points.size(); i++)
	{
		wood_points[i]->Update(deltatime);
	}
}