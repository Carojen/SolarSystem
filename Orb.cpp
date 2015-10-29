#include "Orb.h"
#include <iostream>
#include <cmath>


Orb::Orb(MyVector position, double mass, const double deltaTime, string name, Color color, char key,bool active, MyVector velocity,bool isMoon, Orb* primary)
: mCurrentPosition(position), mPreviousPosition(position), mMass(mass), mName(name), mColor(color), mKey(key),mIsMoon(isMoon), mPrimary(primary)
{
	mInvMass = 1.0 / mMass;

	mForce = MyVector();
	mDt = deltaTime;
	mIsActive = active;

	firstQuad = true;
	secondQuad = false;
	thirdQuad = false;
	fourthQuad = false;

	mNrOfLaps = 0;

	firstdist = 0;
	seconddist = 0;
	thirddist = 0;
	fourthdist = 0;

	mTime = time_t();

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
	double dist = position.length();
	if (mPrimary != nullptr)
	{
		if (mIsMoon)
		{
			mModScale = pow(10, log10(mPrimary->getPosition().length()) - log10((mPrimary->getPosition() - mCurrentPosition).length()) - 1);
		}		
		dist = (position - mPrimary->getPosition()).length();
	}
	mMaxDist = dist;
	mMinDist = dist;
}

void Orb::update(double dt)
{
	if (mIsActive)
	{
		MyVector newPosition = mCurrentPosition * 2 - mPreviousPosition + mForce * mInvMass * dt *dt;
		mPreviousPosition = mCurrentPosition;
		mCurrentPosition = newPosition;
		double dist = mCurrentPosition.length();

		if (mPrimary != nullptr)
		{
			dist = (mCurrentPosition - mPrimary->getPosition()).length();
		}
		if (mMaxDist < dist)
		{
			mMaxDist = dist;
		}
		if (mMinDist > dist)
		{
			mMinDist = dist;
		}
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

	if (mPrimary != nullptr && mIsMoon)
	{
		pos = (-mPrimary->getPosition() + mCurrentPosition)
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

			if (draw->keyTyped('o'))
			{
				std::cout << std::endl << mName << ": min: " << mMinDist << ", max: " << mMaxDist;
				std::cout << "Laps: " <<mNrOfLaps << ", Dists: "<< firstdist << ", " << seconddist << ", " << thirddist << ", " << fourthdist << endl;
			}

			MyVector pos = mCurrentPosition;

			if (mPrimary != nullptr)
			{
				pos = mCurrentPosition - mPrimary->getPosition();
			}

			if ((firstQuad && pos.mX < 0) 
				|| (secondQuad && pos.mZ < 0)
				|| (thirdQuad && pos.mX > 0)
				|| (fourthQuad && pos.mZ > 0))
			{
				bool temp = firstQuad;
				firstQuad = fourthQuad;
				fourthQuad = thirdQuad;
				thirdQuad = secondQuad;
				secondQuad = temp;

				double dist = pos.length();
				if (firstQuad)
				{
					mNrOfLaps++;
					firstdist = dist;
				}
				else if (secondQuad)
				{
					seconddist = dist;
				}
				else if (thirdQuad)
				{
					thirddist = dist;
				}
				else if (fourthQuad)
				{
					fourthdist = dist;
				}

			}
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