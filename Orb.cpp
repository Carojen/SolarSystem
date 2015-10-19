#include "Orb.h"

Orb::Orb( MyVector position, double mass, double velocity, Color color )
: mCurrentPosition(position), mPreviousPosition(position), mMass(mass), mColor(color)
{
	mInvMass = 1.0 / mMass;

	if( velocity != 0 )
	{
		
	}

}

void Orb::update( double dt )
{
	MyVector newPosition = mCurrentPosition * 2 - mPreviousPosition + mForce * mInvMass * dt *dt;
	mPreviousPosition = mCurrentPosition;
	mCurrentPosition = newPosition;
}

void Orb::draw( DemoHandler* draw )
{	
	float size = mMass / 1000.0;
	draw->drawPoint( Point(mCurrentPosition.mX, mCurrentPosition.mY, mCurrentPosition.mZ), mColor, size );
}

void Orb::addForce( MyVector force )
{
	mForce += force;
}

MyVector Orb::getPosition()
{
	return mCurrentPosition;
}

double Orb::getMass( )
{
	return mMass;
}

double Orb::getInvMass( )
{
	return mInvMass;
}
