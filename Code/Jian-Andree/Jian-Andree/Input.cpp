//Input.cpp

#include "stdafx.h"

#include "Input.h"

Keyboard::Keyboard()
{
	W = false;
	A = false;
	S = false;
	D = false;
}

void Keyboard::setW(bool state)
{
	W  = state;
}

void Keyboard::setA(bool state)
{
	A = state;
}

void Keyboard::setS(bool state)
{
	S = state;
}

void Keyboard::setD(bool state)
{
	D = state;
}

bool Keyboard::getW()
{
	return W;
}

bool Keyboard::getA()
{
	return A;
}

bool Keyboard::getS()
{
	return S;
}

bool Keyboard::getD()
{
	return D;
}