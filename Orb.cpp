#include "Orb.h"

Orb::Orb(MyVector position, double mass, const double deltaTime, Color color, char key, MyVector velocity, Orb* primary)
: mCurrentPosition(position), mPreviousPosition(position), mMass(mass), mColor(color), mKey(key), mPrimary(primary)
{
	mInvMass = 1.0 / mMass;

	mForce = MyVector();
	mDt = deltaTime;
	mIsActive = true;

	//double scale 
	mSize = pow(log10(mMass) - 21, 4) * 0.001; // The moon and Pluto are of size order 22
	//double significand = mMass * pow(10, -log10(mMass));
	//mSize =  scale;

	if (mSize < 0.02)
	{
		mSize = 0.02;
	}
	if (mSize > 2.5)
	{
		mSize = 2.5;
	}

	if (velocity.length() != 0)
	{
		mPreviousPosition = mCurrentPosition - velocity  * mDt;
	}

	mModScale = 1;
	if (mPrimary != nullptr)
	{
		mModScale = pow(10, log10(mPrimary->getPosition().length()) - log10((mPrimary->getPosition() - mCurrentPosition).length()) - 1);
	}
}

void Orb::update(double dt)
{
	if (mIsActive)
	{
		MyVector newPosition = mCurrentPosition * 2 - mPreviousPosition + mForce * mInvMass * dt *dt;
		mPreviousPosition = mCurrentPosition;
		mCurrentPosition = newPosition;
	}
	mDebug = mForce;
	mForce = MyVector();
}

void Orb::draw(DemoHandler* draw, bool debug)
{
	if (draw->keyTyped(mKey))
	{
		mIsActive = !mIsActive;
	}

	MyVector position = MyVector();
	MyVector pos = mCurrentPosition;

	if (mPrimary != nullptr)
	{
		pos = (mPrimary->getPosition() - mCurrentPosition)
			* mModScale
			+ mPrimary->getPosition();
	}

	if (mCurrentPosition.length() > 1)
	{
		double scale = 14 - log10(pos.length());
		position = pos
			* pow(10, -11)
			* 0.5 * scale * scale;
	}

	if (mIsActive)
	{
		mDebug.normalize();
		draw->drawPoint(position.toPoint(), mColor, mSize);
		if (debug)
		{
			MyVector velocity = mCurrentPosition - mPreviousPosition;
			velocity.normalize();

			draw->drawLine(position.toPoint(), (position + mDebug * (1 + mSize )).toPoint(), Color(RED), 0.03);
			draw->drawLine( position.toPoint( ), ( position - velocity *( 1 + mSize ) ).toPoint( ), Color( BLUE ), 0.03 );
		}
	}
	else
	{
		draw->drawPoint(position.toPoint(), Color(GRAY), mSize); draw->drawLine(position.toPoint(), (position + mDebug * (1 + mSize)).toPoint(), Color(GRAY), 0.01);
	}
}


void Orb::addForce(MyVector force)
{
	mForce += force;
}

MyVector Orb::getPosition()
{
	return mCurrentPosition;
}

double Orb::getMass()
{
	return mMass;
}

double Orb::getInvMass()
{
	return mInvMass;
}

bool Orb::isActive()
{
	return mIsActive;
}