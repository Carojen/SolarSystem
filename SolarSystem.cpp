#include "SolarSystem.h"


SolarSystem::SolarSystem()
{
	mG = 6.6743 * pow( 10, -11 );
	mDeltaTime = 1.0;
	mPaused = true;
	mDebug = false;
	mNrOfLoops = 1;

	//SUN
	Orb* sun = new Orb(MyVector(0, 0, 0), 1.98855 * pow(10, 30), mDeltaTime, "Sun", Color(YELLOW), '0', true);
	mOrbs.push_back(sun);
	//MERCURY
	mOrbs.push_back(new Orb(MyVector(5.79 * pow(10, 10), 0, 0), 3.3011 * pow(10, 23), mDeltaTime, "Mercury", Color(PINK), '1', true, MyVector(0, 0, 47400), false, sun));
	//VENUS
	mOrbs.push_back(new Orb(MyVector(1.082* pow(10, 11), 0, 0), 4.87 * pow(10, 24), mDeltaTime, "Venus", Color(YELLOW), '2', true, MyVector(0, 0, 35000),false, sun));
	//EARTH
	Orb* earth = new Orb(MyVector(1.496 * pow(10, 11), 0, 0), 5.976 * pow(10, 24), mDeltaTime, "Tellus", Color(BLUE), '3', true, MyVector(0, 0, 29800),false, sun);
	mOrbs.push_back(earth); //v = 29800
	//Moon
	mOrbs.push_back(new Orb(MyVector(1.496 * pow(10, 11) + 3.78 * pow(10, 5), 0, 0), 7.342 * pow(10, 22), mDeltaTime, "Moon", Color(MAGENTA), 'm',true, MyVector(0, 0, 1022),true, earth)); //v=1022

	//MARS
	mOrbs.push_back(new Orb(MyVector(2.279*pow(10, 11), 0, 0), 6.42*pow(10, 23), mDeltaTime, "Mars", Color(RED), '4', true, MyVector(0, 0, 24100),false, sun));
	//JUPITER
	mOrbs.push_back(new Orb(MyVector(7.786 * pow(10, 11), 0, 0), 1.8986 * pow(10, 27), mDeltaTime, "Jupiter", Color(RED), '5', false, MyVector(0, 0, 131000)));
	//SATURN
	mOrbs.push_back(new Orb(MyVector(1.433* pow(10, 12), 0, 0), 5.69* pow(10, 26), mDeltaTime, "Saturn", Color(YELLOW), '6', false, MyVector(0, 0, 9600)));
	//URANUS
	mOrbs.push_back(new Orb(MyVector(2.873*pow(10, 12), 0, 0), 8.68* pow(10, 25), mDeltaTime, "Uranus", Color(GREEN), '7', false, MyVector(0, 0, 6800)));
	//NEPTUNE
	mOrbs.push_back(new Orb(MyVector(4.495*pow(10, 12), 0, 0), 1.03* pow(10, 26), mDeltaTime, "Neptune", Color(CYAN), '8', false, MyVector(0, 0, 5400)));
	//PLUTO
	mOrbs.push_back(new Orb(MyVector(5.906 * pow(10, 12), 0, 0), 1.46*pow(10, 22), mDeltaTime, "Pluto", Color(PINK), '9', false, MyVector(0, 0, 4740)));
	
}
void SolarSystem::reset()
{
	mDeltaTime = 1.0;
	mPaused = true;
	mDebug = false;
	mNrOfLoops = 1;

	//SUN
	mOrbs.push_back(new Orb(MyVector(0, 0, 0), 1.98855 * pow(10, 30), mDeltaTime, "Sun", Color(YELLOW), '0', true));
	//MERCURY
	mOrbs.push_back(new Orb(MyVector(5.79 * pow(10, 10), 0, 0), 3.3011 * pow(10, 23), mDeltaTime, "Mercury", Color(PINK), '1', true, MyVector(0, 0, 47400)));
	//VENUS
	mOrbs.push_back(new Orb(MyVector(1.082* pow(10, 11), 0, 0), 4.87 * pow(10, 24), mDeltaTime, "Venus", Color(YELLOW), '2', true, MyVector(0, 0, 35000)));
	//EARTH
	Orb* earth = new Orb(MyVector(1.496 * pow(10, 11), 0, 0), 5.976 * pow(10, 24), mDeltaTime, "Tellus", Color(BLUE), '3', true, MyVector(0, 0, 29800));
	mOrbs.push_back(earth); //v = 29800
	//Moon
	mOrbs.push_back(new Orb(MyVector(1.496 * pow(10, 11) + 3.78 * pow(10, 5), 0, 0), 7.342 * pow(10, 22), mDeltaTime, "Moon", Color(MAGENTA), 'm',true, MyVector(0, 0, 1022),true, earth)); //v=1022

	//MARS
	mOrbs.push_back(new Orb(MyVector(2.279*pow(10, 11), 0, 0), 6.42*pow(10, 23), mDeltaTime, "Mars", Color(RED), '4', true, MyVector(0, 0, 24100)));
	//JUPITER
	mOrbs.push_back(new Orb(MyVector(7.786 * pow(10, 11), 0, 0), 1.8986 * pow(10, 27), mDeltaTime, "Jupiter", Color(RED), '5', false, MyVector(0, 0, 131000)));
	//SATURN
	mOrbs.push_back(new Orb(MyVector(1.433* pow(10, 12), 0, 0), 5.69* pow(10, 26), mDeltaTime, "Saturn", Color(YELLOW), '6', false, MyVector(0, 0, 9600)));
	//URANUS
	mOrbs.push_back(new Orb(MyVector(2.873*pow(10, 12), 0, 0), 8.68* pow(10, 25), mDeltaTime, "Uranus", Color(GREEN), '7', false, MyVector(0, 0, 6800)));
	//NEPTUNE
	mOrbs.push_back(new Orb(MyVector(4.495*pow(10, 12), 0, 0), 1.03* pow(10, 26), mDeltaTime, "Neptune", Color(CYAN), '8', false, MyVector(0, 0, 5400)));
	//PLUTO
	mOrbs.push_back(new Orb(MyVector(5.906 * pow(10, 12), 0, 0), 1.46*pow(10, 22), mDeltaTime, "Pluto", Color(PINK), '9', false, MyVector(0, 0, 4740)));
}


void SolarSystem::update( DemoHandler* dh )
{	
	if( dh->keyTyped( 'r' ) )
	{
		mOrbs.clear();

		reset();
	}

	if( dh->keyTyped( 'p' ) )
	{
		mPaused = !mPaused;
	}
	if( dh->keyTyped( 'd' ) )
	{
		mDebug = !mDebug;
	}

	if (dh->keyTyped('+'))
	{
		if (mNrOfLoops < 1000000)
		{
			mNrOfLoops = (int) (mNrOfLoops * 10);
		}
	}

	if (dh->keyTyped('-'))
	{
		if (mNrOfLoops > 1)
		{
			mNrOfLoops = (int) (mNrOfLoops / 10);
		}
	}

	if( !mPaused )
	{
		int limit = mOrbs.size();
		for( unsigned int j = 0; j < mNrOfLoops; j++ )
		{
			for( unsigned int i = 0; i < limit - 1; i++ )
			{
				for( unsigned int k = i + 1; k < limit; k++ )
				{
					addForce( mOrbs[i], mOrbs[k] );											
				}								
			}

			for each( Orb* o in mOrbs )
			{
				o->update( mDeltaTime );				
			}
		}
	}
	
	draw( dh );
}

void SolarSystem::draw( DemoHandler* draw )
{	
	for each( Orb* o in mOrbs )
	{
		o->draw(draw, mDebug);
	}
}

void SolarSystem::addForce( Orb* one, Orb* two )
{
	if( one->isActive() && two->isActive() )
	{
		MyVector r = one->getPosition() - two->getPosition();
		double l = r.length();
		if( l > 1000 )
		{
			double force = mG* one->getMass() * two->getMass()
				/ ( l * l );

			r.normalize();

			one->addForce( r * -force );
			two->addForce( r *  force );
		}
	}
}