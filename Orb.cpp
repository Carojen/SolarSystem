#include "Orb.h"

Orb::Orb( MyVector position, double mass, const double deltaTime, Color color, char key, MyVector velocity, Orb* primary )
: mCurrentPosition( position ), mPreviousPosition( position ), mMass( mass ), mColor( color ), mKey(key), mPrimary( primary )
{
	mInvMass = 1.0 / mMass;

	mForce = MyVector( );
	mDt = deltaTime;
	mIsActive = true;

	int scale =  pow(log10( mMass ) - 21, 3); // The moon and Pluto are of size order 22
	int tLog = - (3 + log10( mMass ));	
	mSize = mMass * pow(10, tLog) * scale;
	
	if( velocity.length() != 0 )
	{
		mPreviousPosition = mCurrentPosition - velocity  * mDt;
	}
	mModScale = 1;
	if( mPrimary != nullptr )
	{
		mModScale = log10( mPrimary->getPosition().length()) - log10(( mPrimary->getPosition() - mCurrentPosition ).length());
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
	if( draw->keyTyped( mKey ) )
	{
		mIsActive = !mIsActive;
	}
	MyVector position = MyVector();
	MyVector pos = mCurrentPosition;

	if( mPrimary != nullptr )
	{
		pos = ( mPrimary->getPosition() - mCurrentPosition )
			* pow(10, mModScale - 1) 
			+ mPrimary->getPosition();
	}

	if( mCurrentPosition.length( ) > 1 )
	{
		position = pos
			* pow( 10, -11 )
			* 0.5
			* pow( 14 - log10( pos.length()), 2 ); // 0 - 2
	}	
	if( mIsActive )
	{
		draw->drawPoint( position.toPoint(), mColor, mSize );
	}
	else
	{
		draw->drawPoint( position.toPoint( ), Color(GRAY), mSize );
	}
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

bool Orb::isActive()
{
	return mIsActive;
}