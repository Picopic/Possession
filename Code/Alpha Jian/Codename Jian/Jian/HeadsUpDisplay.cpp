//HeadsUpDisplay.cpp

#include "stdafx.h"

#include "Enums.h"
#include "Vector2.h"

#include "AnimatedSprite.h"
#include "SpriteManager.h"
#include "HeadsUpDisplay.h"

HeadsUpDisplay::HeadsUpDisplay()
{

}

bool HeadsUpDisplay::Initialise(SpriteManager* sprite_mgr)
{
	sprite_manager = sprite_mgr;

	hud_arrow = sprite_mgr->Load("Placeholder HUD .png", 1, 1, 65, 65, 195, 0);
	if(hud_arrow == nullptr)	return false;

	symbols.push_back(sprite_mgr->Load("Placeholder HUD .png", 1, 1, 65, 65, 0, 0));
	if(symbols[symbols.size() - 1] == nullptr) return false;
	symbols.push_back(sprite_mgr->Load("Placeholder HUD .png", 1, 1, 65, 65, 65, 0));
	if(symbols[symbols.size() - 1] == nullptr) return false;
	symbols.push_back(sprite_mgr->Load("Placeholder HUD .png", 1, 1, 65, 65, 130, 0));
	if(symbols[symbols.size() - 1] == nullptr) return false;

	//Give them their positions
	hud_arrow->getSprite()->setPosition(20, 80);

	for(int i = 0; i < symbols.size(); i++)
	{
		symbols[i]->getSprite()->setPosition(80, 80 + (i * 65));
	}
	
	//
	current_fire_pos = 80;
	current_water_pos = 80;
	current_wood_pos = 80;
	//
	
	Update(0);

	return true;
}

void HeadsUpDisplay::Cleanup()
{
	if(sprite_manager != nullptr)
	{
		delete sprite_manager;
		sprite_manager = nullptr;
	}

	if(hud_arrow != nullptr)
	{
		delete hud_arrow;
		hud_arrow = nullptr;
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

void HeadsUpDisplay::Move(float x, float y)
{
	current_fire_pos += x;
	current_water_pos += x;
	current_wood_pos += x;

	//arrow
	hud_arrow->getSprite()->move(x, y);
	
	//symbols
	for(int i = 0; i < symbols.size(); i++)
	{
		symbols[i]->getSprite()->move(x, y);
	}
	//fire
	for(int i = 0; i < fire_points.size(); i++)
	{
		fire_points[i]->getSprite()->move(x, y);
	}
	//water
	for(int i = 0; i < water_points.size(); i++)
	{
		water_points[i]->getSprite()->move(x, y);
	}
	//wood
	for(int i = 0; i < wood_points.size(); i++)
	{
		wood_points[i]->getSprite()->move(x, y);
	}
}

void HeadsUpDisplay::AddElementalPoint(Type Elemental_type)
{
	switch(Elemental_type)
	{
	case FIRE:
		fire_points.push_back(sprite_manager->Load("Placeholder HUD .png", 1, 1, 65, 65, 65, 65));
		fire_points[fire_points.size() - 1]->getSprite()->setPosition(current_fire_pos + 50, 145);
		current_fire_pos += 50;
		break;
	case WATER:
		water_points.push_back(sprite_manager->Load("Placeholder HUD .png", 1, 1, 65, 65, 0, 65));
		water_points[water_points.size() - 1]->getSprite()->setPosition(current_water_pos + 50, 80);
		current_water_pos += 50;
		break;
	case WOOD:
		wood_points.push_back(sprite_manager->Load("Placeholder HUD .png", 1, 1, 65, 65, 130, 65));
		wood_points[wood_points.size() - 1]->getSprite()->setPosition(current_wood_pos + 50, 210);
		current_wood_pos += 50;
		break;
	}
}

void HeadsUpDisplay::DeleteElementalPoint(Type element_type)
{
	switch (element_type)
	{
	case FIRE:
		if(fire_points.size() > 0)
		{
			delete fire_points[fire_points.size() - 1];
			fire_points[fire_points.size() - 1] = nullptr;
			fire_points.erase(fire_points.begin() + (fire_points.size() - 1));
			current_fire_pos -= 50;
		}
		break;
	case WATER:
		if(water_points.size() > 0)
		{
			delete water_points[water_points.size() - 1];
			water_points[water_points.size() - 1] = nullptr;
			water_points.erase(water_points.begin() + (water_points.size() - 1));
			current_water_pos -= 50;
		}
		break;
	case WOOD:
		if(wood_points.size() > 0)
		{
			delete wood_points[wood_points.size() - 1];
			wood_points[wood_points.size() - 1] = nullptr;
			wood_points.erase(wood_points.begin() + (wood_points.size() - 1));
			current_wood_pos -= 50;
		}
		break;
	}
}

void HeadsUpDisplay::MoveArrow(Type type)
{
	switch(type)
	{
	case FIRE:
		hud_arrow->getSprite()->setPosition(hud_arrow->getSprite()->getPosition().x, 145);
		break;
	case WATER:
		hud_arrow->getSprite()->setPosition(hud_arrow->getSprite()->getPosition().x, 80);
		break;
	case WOOD:
		hud_arrow->getSprite()->setPosition(hud_arrow->getSprite()->getPosition().x, 210);
		break;
	}
}