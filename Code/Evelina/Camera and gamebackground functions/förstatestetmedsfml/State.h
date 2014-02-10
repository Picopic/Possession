/*	State.h
	This is a template for all the other states.
*/

#pragma once

#include "stdafx.h"

#include <string>
#include <iostream>

class State{
public:
	virtual ~State(){};
	virtual bool Initialize()=0;
	virtual bool Enter()=0;
	virtual bool Exit()=0;
	virtual bool Update()=0;

	//Dessa �r de som Jerry tipsade om, nedan kommer ytterligare n�gra
	//String hanterar text, IsType returns true if type equals current state
	virtual std::string Next()=0;
	virtual bool IsType(const std::string& Type)=0;
	//Cleanup �r valfri, g�r �ven att k�ra i dekonstruktorn
	//virtual void Cleanup()=0;
	//Draw g�r att ha i Update, men blir snyggare som egen. Allt som visas p� sk�rmen har man i Draw.
	virtual bool Draw() = 0;
};