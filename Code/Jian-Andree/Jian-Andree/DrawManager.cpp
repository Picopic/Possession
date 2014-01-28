//Drawmanager.cpp
#include "stdafx.h"
#include "DrawManager.h"



DrawManager::DrawManager()
{

}

void DrawManager::Draw(RenderWindow *window)
{
	window->clear(Color(0x11,0x22,0x33,0xff));

	window->display();
}