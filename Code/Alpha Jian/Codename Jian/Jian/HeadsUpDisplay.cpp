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

	active_points = FIRE;

	symbol_width = 100;
	symbol_height = 100;

	for(int i = 0; i < 3; i++)
	{
		hud_indicator.push_back(sprite_mgr->Load("Elements GUI.png", 1, 1, symbol_width, symbol_height, 0, i*symbol_height));
		if(hud_indicator[i] == nullptr)	return false;
	}
	current_indicator = hud_indicator[0];

	//symbols
	symbols.push_back(sprite_mgr->Load("Elements GUI.png", 1, 1, symbol_width, symbol_height, symbol_width, 0));
	if(symbols[symbols.size() - 1] == nullptr) return false;
	symbols.push_back(sprite_mgr->Load("Elements GUI.png", 1, 1, symbol_width, symbol_height, symbol_width, symbol_height));
	if(symbols[symbols.size() - 1] == nullptr) return false;
	symbols.push_back(sprite_mgr->Load("Elements GUI.png", 1, 1, symbol_width, symbol_height, symbol_width, symbol_height*2));
	if(symbols[symbols.size() - 1] == nullptr) return false;

	//Give them their positions
	for(int i = 0; i < hud_indicator.size(); i++)
	{
		hud_indicator[i]->getSprite()->setPosition(60, 20 + symbol_height);
	}

	symbols[0]->getSprite()->setPosition(60, 20 + symbol_height);
	symbols[1]->getSprite()->setPosition(20, 40);
	symbols[2]->getSprite()->setPosition(20, 2*symbol_height);

	for(int i = 0; i < symbols.size(); i++)
		symbol_positions.push_back(symbols[i]->getSprite()->getPosition());

	x_offset = 25;
	y_offset = 25;

	//
	current_fire_pos = symbols[0]->getSprite()->getPosition().x + symbol_width/2;
	current_water_pos = symbols[0]->getSprite()->getPosition().x + symbol_width/2;
	current_wood_pos = symbols[0]->getSprite()->getPosition().x + symbol_width/2;
	//

	//Empty points
	current_empty_fire = current_fire_pos + 10 * x_offset;
	current_empty_water = current_water_pos + 10 * x_offset;
	current_empty_wood = current_wood_pos + 10 * x_offset;

	for(int i = 0; i < 10; i++)
	{
		AddEmptyPoint(FIRE);
		AddEmptyPoint(WATER);
		AddEmptyPoint(WOOD);
	}

	return true;
}

void HeadsUpDisplay::Cleanup()
{
	if(sprite_manager != nullptr)
	{
		delete sprite_manager;
		sprite_manager = nullptr;
	}

	//Hud indicator
	for(int i = 0; i < hud_indicator.size(); i++)
	{
		if(hud_indicator[i] != nullptr)
		{
			delete hud_indicator[i];
			hud_indicator[i] = nullptr;
		}
	}
	if(current_indicator != nullptr)
	{
		delete current_indicator;
		current_indicator = nullptr;
	}
	

	//symbols
	for(int i = 0; i < symbols.size(); i++)
	{
		delete symbols[i];
		symbols[i] = nullptr;
	}

	//Empty points
	for(int i = 0; i < empty_fire.size(); i++)
	{
		if(empty_fire[i] != nullptr)
		{
			delete empty_fire[i];
			empty_fire[i] = nullptr;
		}
	}
	for(int i = 0; i < empty_water.size(); i++)
	{
		if(empty_water[i] != nullptr)
		{
			delete empty_water[i];
			empty_water[i] = nullptr;
		}
	}
	for(int i = 0; i < empty_wood.size(); i++)
	{
		if(empty_wood[i] != nullptr)
		{
			delete empty_wood[i];
			empty_wood[i] = nullptr;
		}
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
	//symbols
	for(int i = 0; i < symbols.size(); i++)
	{
		window->draw(*symbols[i]->getSprite());
	}

	switch (active_points)
	{
	case FIRE:
			//fire
		for(int i = 0; i < empty_fire.size(); i++)
		{
			window->draw(*empty_fire[i]->getSprite());
		}
		for(int i = 0; i < fire_points.size(); i++)
		{
			window->draw(*fire_points[i]->getSprite());
		}
		break;
	case WATER:
			//water
		for(int i = 0; i < empty_water.size(); i++)
		{
			window->draw(*empty_water[i]->getSprite());
		}
		for(int i = 0; i < water_points.size(); i++)
		{
			window->draw(*water_points[i]->getSprite());
		}
		break;
	case WOOD:
			//wood
		for(int i = 0; i < empty_wood.size(); i++)
		{
			window->draw(*empty_wood[i]->getSprite());
		}
		for(int i = 0; i < wood_points.size(); i++)
		{
			window->draw(*wood_points[i]->getSprite());
		}
		break;
	}

	//Indicator
	window->draw(*current_indicator->getSprite());
}

void HeadsUpDisplay::Update(float deltatime)
{
	//arrow
	current_indicator->Update(deltatime);
	
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

	current_empty_fire += x;
	current_empty_water += x;
	current_empty_wood += x;

	//current indicator
	current_indicator->getSprite()->move(x, y);

	for(int i = 0; i < symbol_positions.size(); i++)
	{
		symbol_positions[i].x += x;
		symbol_positions[i].y += y;
	}

	//indicators
	for(int i = 0; i < hud_indicator.size(); i++)
	{
		if(current_indicator != hud_indicator[i])
		{
			hud_indicator[i]->getSprite()->move(x, y);
		}
	}

	//Empty points
	for(int i = 0; i < empty_fire.size(); i++)
	{
		empty_fire[i]->getSprite()->move(x, y);
	}
	for(int i = 0; i < empty_water.size(); i++)
	{
		empty_water[i]->getSprite()->move(x, y);
	}
	for(int i = 0; i < empty_wood.size(); i++)
	{
		empty_wood[i]->getSprite()->move(x, y);
	}
	
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
		DeleteEmptyPoint(FIRE);
		if(fire_points.size() < 10)
		{
			if(fire_points.size()%2 == 1)
			{
				fire_points.push_back(sprite_manager->Load("Elements GUI.png", 1, 1, symbol_width, symbol_height, symbol_width*2, symbol_height*0));
				fire_points[fire_points.size() - 1]->getSprite()->setPosition(current_fire_pos + x_offset, symbol_positions[0].y);
				current_fire_pos += x_offset;
			}
			else
			{
				fire_points.push_back(sprite_manager->Load("Elements GUI.png", 1, 1, symbol_width, symbol_height, symbol_width*2, symbol_height*0));
				fire_points[fire_points.size() - 1]->getSprite()->setPosition(current_fire_pos + x_offset, symbol_positions[0].y + y_offset);
				current_fire_pos += x_offset;
			}
		}
		
		break;
	case WATER:
		DeleteEmptyPoint(WATER);
		if(water_points.size() < 10)
		{
			if(water_points.size()%2 == 1)
			{
				water_points.push_back(sprite_manager->Load("Elements GUI.png", 1, 1, symbol_width, symbol_height, symbol_width*2, symbol_height*1));
				water_points[water_points.size() - 1]->getSprite()->setPosition(current_water_pos + x_offset, symbol_positions[0].y);
				current_water_pos += x_offset;
			}
			else
			{
				water_points.push_back(sprite_manager->Load("Elements GUI.png", 1, 1, symbol_width, symbol_height, symbol_width*2, symbol_height*1));
				water_points[water_points.size() - 1]->getSprite()->setPosition(current_water_pos + x_offset, symbol_positions[0].y + y_offset);
				current_water_pos += x_offset;
			}
		}
		break;
	case WOOD:
		DeleteEmptyPoint(WOOD);
		if(wood_points.size() < 10)
		{
			if(wood_points.size()%2 == 1)
			{
				wood_points.push_back(sprite_manager->Load("Elements GUI.png", 1, 1, symbol_width, symbol_height, symbol_width*2, symbol_height*2));
				wood_points[wood_points.size() - 1]->getSprite()->setPosition(current_wood_pos + x_offset, symbol_positions[0].y);
				current_wood_pos += x_offset;
			}
			else
			{
				wood_points.push_back(sprite_manager->Load("Elements GUI.png", 1, 1, symbol_width, symbol_height, symbol_width*2, symbol_height*2));
				wood_points[wood_points.size() - 1]->getSprite()->setPosition(current_wood_pos + x_offset, symbol_positions[0].y + y_offset);
				current_wood_pos += x_offset;
			}
		}
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
			AddEmptyPoint(FIRE);
			delete fire_points[fire_points.size() - 1];
			fire_points[fire_points.size() - 1] = nullptr;
			fire_points.erase(fire_points.begin() + (fire_points.size() - 1));
			current_fire_pos -= x_offset;
		}
		break;
	case WATER:
		if(water_points.size() > 0)
		{
			AddEmptyPoint(WATER);
			delete water_points[water_points.size() - 1];
			water_points[water_points.size() - 1] = nullptr;
			water_points.erase(water_points.begin() + (water_points.size() - 1));
			current_water_pos -= x_offset;
		}
		break;
	case WOOD:
		if(wood_points.size() > 0)
		{
			AddEmptyPoint(WOOD);
			delete wood_points[wood_points.size() - 1];
			wood_points[wood_points.size() - 1] = nullptr;
			wood_points.erase(wood_points.begin() + (wood_points.size() - 1));
			current_wood_pos -= x_offset;
		}
		break;
		//Empty points
	case NONE:
		break;
	}
}

void HeadsUpDisplay::MoveIndicator(Type type)
{
	switch(type)
	{
	case FIRE:
		current_indicator = hud_indicator[0];
		symbols[0]->getSprite()->setPosition(symbol_positions[0]);
		symbols[1]->getSprite()->setPosition(symbol_positions[1]);
		symbols[2]->getSprite()->setPosition(symbol_positions[2]);
		active_points = type;
		break;
	case WATER:
		current_indicator = hud_indicator[1];
		symbols[0]->getSprite()->setPosition(symbol_positions[2]);
		symbols[1]->getSprite()->setPosition(symbol_positions[0]);
		symbols[2]->getSprite()->setPosition(symbol_positions[1]);
		active_points = type;
		break;
	case WOOD:
		current_indicator = hud_indicator[2];
		symbols[0]->getSprite()->setPosition(symbol_positions[1]);
		symbols[1]->getSprite()->setPosition(symbol_positions[2]);
		symbols[2]->getSprite()->setPosition(symbol_positions[0]);
		active_points = type;
		break;
	}
}

void HeadsUpDisplay::AddEmptyPoint(Type element_type)
{
	switch (element_type)
	{
	case FIRE:
		if(empty_fire.size()%2 == 1)
		{
			empty_fire.push_back(sprite_manager->Load("Elements GUI.png", 1, 1, symbol_width, symbol_height, 0, 3*symbol_height));
			empty_fire[empty_fire.size() - 1]->getSprite()->setPosition(current_empty_fire, symbol_positions[0].y + y_offset);
			current_empty_fire -= x_offset;
		}
		else
		{
			empty_fire.push_back(sprite_manager->Load("Elements GUI.png", 1, 1, symbol_width, symbol_height, 0, 3*symbol_height));
			empty_fire[empty_fire.size() - 1]->getSprite()->setPosition(current_empty_fire, symbol_positions[0].y);
			current_empty_fire -= x_offset;
		}
		break;
	case WATER:
		if(empty_water.size()%2 == 1)
		{
			empty_water.push_back(sprite_manager->Load("Elements GUI.png", 1, 1, symbol_width, symbol_height, 0, 3*symbol_height));
			empty_water[empty_water.size() - 1]->getSprite()->setPosition(current_empty_water, symbol_positions[0].y + y_offset);
			current_empty_water -= x_offset;
		}
		else
		{
			empty_water.push_back(sprite_manager->Load("Elements GUI.png", 1, 1, symbol_width, symbol_height, 0, 3*symbol_height));
			empty_water[empty_water.size() - 1]->getSprite()->setPosition(current_empty_water, symbol_positions[0].y);
			current_empty_water -= x_offset;
		}
		break;
	case WOOD:
		if(empty_wood.size()%2 == 1)
		{
			empty_wood.push_back(sprite_manager->Load("Elements GUI.png", 1, 1, symbol_width, symbol_height, 0, 3*symbol_height));
			empty_wood[empty_wood.size() - 1]->getSprite()->setPosition(current_empty_wood, symbol_positions[0].y + y_offset);
			current_empty_wood -= x_offset;
		}
		else
		{
			empty_wood.push_back(sprite_manager->Load("Elements GUI.png", 1, 1, symbol_width, symbol_height, 0, 3*symbol_height));
			empty_wood[empty_wood.size() - 1]->getSprite()->setPosition(current_empty_wood, symbol_positions[0].y);
			current_empty_wood -= x_offset;
		}
		break;
	}
}

void HeadsUpDisplay::DeleteEmptyPoint(Type element_type)
{
	switch (element_type)
	{
	case FIRE:
		if(empty_fire.size() > 0)
		{
			delete empty_fire[empty_fire.size() - 1];
			empty_fire[empty_fire.size() - 1] = nullptr;
			empty_fire.erase(empty_fire.begin() + (empty_fire.size() - 1));
			current_empty_fire += x_offset;
		}
		break;
	case WATER:
		if(empty_water.size() > 0)
		{
			delete empty_water[empty_water.size() - 1];
			empty_water[empty_water.size() - 1] = nullptr;
			empty_water.erase(empty_water.begin() + (empty_water.size() - 1));
			current_empty_water += x_offset;
		}
		break;
	case WOOD:
		if(empty_wood.size() > 0)
		{
			delete empty_wood[empty_wood.size() - 1];
			empty_wood[empty_wood.size() - 1] = nullptr;
			empty_wood.erase(empty_wood.begin() + (empty_wood.size() - 1));
			current_empty_wood += x_offset;
		}
		break;
	}
}