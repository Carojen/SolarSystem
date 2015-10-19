#include "Orb.h"

Orb::Orb( MyVector position, double mass, const double deltaTime, Color color, MyVector velocity )
: mCurrentPosition(position), mPreviousPosition(position), mMass(mass), mColor(color)
{
	mInvMass = 1.0 / mMass;

	mForce = MyVector( );

	int scale =  pow(log10( mMass ) - 21, 3); // The moon and Pluto are of size order 22; this line should return a number between 1 and 81
	int tLog = - (3 + log10( mMass ));	
	mSize = mMass * pow(10, tLog) * scale;
	
	if( velocity.length() != 0 )
	{
		mPreviousPosition = mCurrentPosition - velocity  * deltaTime;
	}
	scale = 0;
}

void Orb::update( double dt )
{
	MyVector newPosition = mCurrentPosition * 2 - mPreviousPosition + mForce * mInvMass * dt *dt;
	mPreviousPosition = mCurrentPosition;
	mCurrentPosition = newPosition;

	mForce = MyVector();
}

void Orb::draw( DemoHandler* draw )
{
	MyVector position = mCurrentPosition 
		* pow( 10, -11) 
		* pow(14 - log10(mCurrentPosition.length()),2); // 0 - 2
	draw->drawPoint( position.toPoint(), mColor, mSize );
}

void Orb::addForce( MyVector force )
{
	mForce += force;
	force *= 1;
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
