//Input.h

#pragma once

class Keyboard
{
	bool W, A, S, D;

public:
	Keyboard();

	bool getW();
	bool getA();
	bool getS();
	bool getD();

	void setW(bool state);
	void setA(bool state);
	void setS(bool state);
	void setD(bool state);
};