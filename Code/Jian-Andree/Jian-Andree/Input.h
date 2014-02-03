//Input.h

#pragma once

class Keyboard
{
	bool W, A, S, D, R;

public:
	Keyboard();

	bool getW();
	bool getA();
	bool getS();
	bool getD();
	bool getR();

	void setW(bool state);
	void setA(bool state);
	void setS(bool state);
	void setD(bool state);
	void setR(bool state);
};