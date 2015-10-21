#include "Orb.h"

Orb::Orb( MyVector position, double mass, const double deltaTime, Color color, char key, MyVector velocity, Orb* primary )
: mCurrentPosition( position ), mPreviousPosition( position ), mMass( mass ), mColor( color ), mKey(key), mPrimary( primary )
{
	mInvMass = 1.0 / mMass;

	mForce = MyVector();
	mDt = deltaTime;
	mIsActive = true;

	double scale =  pow(log10( mMass ) - 21, 4) * 0.001; // The moon and Pluto are of size order 22
	double significand = mMass * pow(10, - log10( mMass ));	
	mSize = significand * scale;

	if( mSize < 0.02 )
	{
		mSize = 0.02;
	}
	if( mSize > 2.5 )
	{
		mSize = 2.5;
	}
	
	if( velocity.length() != 0 )
	{
		mPreviousPosition = mCurrentPosition - velocity  * mDt;
	}

	mModScale = 1;
	MyVector pos = mCurrentPosition;

	if( mPrimary != nullptr )
	{
		mModScale = pow(10,log10( mPrimary->getPosition().length()) - log10(( mPrimary->getPosition() - mCurrentPosition ).length())-1);

		pos = (mPrimary->getPosition() - mCurrentPosition)
			* mModScale
			+ mPrimary->getPosition();
	}
	if (mCurrentPosition.length() > 1)
	{
		mDistScale = 14 - log10(pos.length());
		mDistScale = mDistScale * mDistScale * pow(10, -11)* 0.5;
	}
}

void Orb::update( double dt )
{
	if( mIsActive && (mPrimary == nullptr || mPrimary->isActive() ))
	{
		MyVector newPosition = mCurrentPosition * 2 - mPreviousPosition + mForce * mInvMass * dt *dt;
		mPreviousPosition = mCurrentPosition;
		mCurrentPosition = newPosition;		
	}	
	mDebug = mForce;
	mForce = MyVector();
}

void Orb::draw( DemoHandler* draw, bool debug )
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
			* mModScale
			+ mPrimary->getPosition();
	}

	if( mCurrentPosition.length( ) > 1 )
	{
		position = pos
			* mDistScale;
	}	
		
	if( mIsActive )
	{		
		if (position.length() > 1000)
		{
			mIsActive = false;
		}
		draw->drawPoint( position.toPoint(), mColor, mSize );	
		if( debug )
		{
			mDebug.normalize();
			draw->drawLine( position.toPoint( ), ( position + mDebug *(1+mSize)).toPoint( ), Color( mColor ), 0.01 );
		}
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