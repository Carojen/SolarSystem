#pragma once
#include "Point.h"
#include <cmath>

class MyVector
{
public:
	MyVector()
	{
		mX = 0;
		mY = 0;
		mZ = 0;
	}
    MyVector(double x,double y)
	{
		mX = x;
		mY = y;
		mZ = 0;
	}
	MyVector(double x,double y,double z)
	{
		mX = x;
		mY = y;
		mZ = z;
	}
	MyVector(const MyVector& v2)
	{
		mX = v2.mX;
		mY = v2.mY;
		mZ = v2.mZ;
	}
	MyVector(const Point& p)
	{
		mX = p.mX;
		mY = p.mY;
		mZ = p.mZ;
	}
	~MyVector(void)
	{
	}


	MyVector operator+(const MyVector& v2)
	{
		return MyVector(mX + v2.mX, mY + v2.mY, mZ + v2.mZ);
	}
	
	void operator+= (const MyVector& v2)
	{
		mX += v2.mX;
		mY += v2.mY;
		mZ += v2.mZ;
	}
	
	MyVector operator-(const MyVector& v2)
	{
		return MyVector(mX - v2.mX , mY - v2.mY , mZ - v2.mZ);
	}
    
	MyVector operator-()
	{
		return MyVector(-mX, -mY, -mZ);
	}
	void operator-= (const MyVector& v2)
	{
		mX -= v2.mX;
		mY -= v2.mY;
		mZ -= v2.mZ;
	}
	
	MyVector operator%(const MyVector& v2)
	{
		return MyVector(mY * v2.mZ - mZ * v2.mY ,
                        mZ * v2.mX - mX * v2.mZ ,
                        mX * v2.mY - mY * v2.mX);
	}
	
	double operator*(const MyVector& v2)
	{
		return mX * v2.mX + mY * v2.mY + mZ * v2.mZ;
	}
	
	MyVector operator*(const double& f)
	{
		return MyVector(mX * f, mY * f, mZ * f);
	}
	
	void operator*= (const double& f)
	{
		mX *= f;
		mY *= f;
		mZ *= f;
	}
	
	double length()
	{
		return sqrt(mX*mX+mY*mY+mZ*mZ);
	}
	
	void normalize()
	{
		double l = length();
		if(l>0.000001){
			mX *= 1.0f/l;
			mY *= 1.0f/l;
			mZ *= 1.0f/l;
		}
	}
	
	Point toPoint()
	{
		return Point(mX,mY,mZ);
	}

	double mX, mY, mZ;
};

/*
 (c)2009 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde 
 Contact me if you want to use it for other purposes.
*/