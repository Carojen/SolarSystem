#ifndef ORB_H
#define ORB_H
#include "SF_src\DemoHandler.h"
#include "SF_src\MyVector.h"
class Orb
{
public:
	Orb(MyVector position, double mass, double velocity = 0, Color color=Color(GRAY));
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
	Color mColor;
};
#endif