#ifndef ORB_H
#define ORB_H
#include "SF_src\DemoHandler.h"
#include "SF_src\MyVector.h"
#include <time.h>
class Orb
{
public:
	Orb(MyVector position,
		double mass,
		const double deltaTime,
		string name = "Unknown",
		Color color = Color(GRAY),
		char key = 'a',
		bool active = true,
		MyVector velocity = MyVector(),
		bool isMoon = false,
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
	bool mIsMoon;
	double mModScale;
	double mDistScale;
	bool mIsActive;
	char mKey;
	// Output
	double mMaxDist;
	double mMinDist;
	string mName;

	bool firstQuad;
	bool secondQuad;
	bool thirdQuad;
	bool fourthQuad;

	double firstdist;
	double seconddist;
	double thirddist;
	double fourthdist;


	int mNrOfLaps;

	time_t mTime;

	MyVector mDebug;
};
#endif