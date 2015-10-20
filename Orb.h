#ifndef ORB_H
#define ORB_H
#include "SF_src\DemoHandler.h"
#include "SF_src\MyVector.h"
class Orb
{
public:
	Orb( MyVector position, 
		double mass, 
		const double deltaTime, 
		Color color = Color( GRAY ), 
		char key = 'a',
		MyVector velocity = MyVector( ),		
		Orb* primary = nullptr );

	void update(double deltaTime);
	void draw(DemoHandler* draw, bool debug=false);
	void addForce( MyVector force );
	MyVector getPosition();
	double getMass();
	double getInvMass();
	bool isActive();
	~Orb();
private:
	MyVector mCurrentPosition;
	MyVector mPreviousPosition;
	MyVector mForce;
	double mMass;
	double mInvMass;
	double mSize;
	Color mColor;
	double mDt;
	Orb* mPrimary;
	double mModScale;
	bool mIsActive;
	char mKey;
	MyVector mDebug;
};
#endif