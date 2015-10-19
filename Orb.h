#ifndef ORB_H
#define ORB_H
#include "SF_src\DemoHandler.h"
#include "SF_src\MyVector.h"
class Orb
{
public:
	Orb( MyVector position, double mass, const double deltaTime, Color color = Color( GRAY ), MyVector velocity = MyVector( ) );
	void update(double deltaTime);
	void draw(DemoHandler* draw);
	void addForce( MyVector force );
	MyVector getPosition();
	double getMass();
	double getInvMass();
	~Orb();
private:
	MyVector mCurrentPosition;
	MyVector mPreviousPosition;
	MyVector mForce;
	double mMass;
	double mInvMass;
	double mSize;
	Color mColor;
};
#endif