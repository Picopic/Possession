//// Jian.cpp : Defines the entry point for the console application.
////
//
#include "stdafx.h"
//
//using namespace sf;
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	RenderWindow window(VideoMode(1024, 640), "GAME");
//
//	CircleShape shape(50);
//	shape.setPosition(450, 300);
//
//	while(window.isOpen())
//	{
//		//Event handling
//		Event event;
//		while(window.pollEvent(event))
//		{
//			if(event.type == Event::Closed)
//			{
//				window.close();
//			}
//			if(Event::KeyPressed)
//			{
//				if(event.key.code == Keyboard::Escape)
//				{
//					window.close();
//				}
//			}
//		}
//		
//		//game logic
//		shape.rotate(3);
//		if(Keyboard::isKeyPressed(Keyboard::D))
//		{
//			shape.move(2, 0);
//		}
//		else if(Keyboard::isKeyPressed(Keyboard::A))
//		{
//			shape.move(-2, 0);
//		}
//
//		//drawing portion of loop
//		window.clear(Color(0x11, 0x22, 0x33, 0xff));
//		window.draw(shape);
//		window.display();
//	}
//
//	return 0;
//}
//