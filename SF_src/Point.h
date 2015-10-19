#pragma once
/*
	This class is used to represent a fixed point in 3D-space. 
	It is deliberately simple as you should implement a proper Vector class
	for your calculations. Use this only in the communication with the DemoHandler.
*/

class Point
{
public:
	float mX,mY,mZ;
	Point(){mX = 0;mY = 0;mZ = 0;}
	Point(const float X,const float Y,const float Z)
	{
		mX = X;
		mY = Y;
		mZ = Z;
	}
};


/*
	(c)2009 Henrik Engstršm, henrik.engstrom@his.se
	This code may only be used by students in the Game Physics course at the University of Skšvde 
	Contact me if you want to use it for other purposes.
*/