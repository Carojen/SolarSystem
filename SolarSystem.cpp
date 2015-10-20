#include "SolarSystem.h"


SolarSystem::SolarSystem()
{
	mG = 6.6743 * pow( 10, -11 );
	mDeltaTime = 1.0/30.0;
	mPaused = true;
	mDebug = false;

	//SUN
	mOrbs.push_back( new Orb( MyVector( 0, 0, 0 ), 1.98855 * pow(10,30), mDeltaTime,Color( YELLOW ), '0'));
	//MERCURY
	mOrbs.push_back( new Orb( MyVector( 5.79 * pow( 10, 10 ), 0, 0 ), 3.3011 * pow( 10, 23 ), mDeltaTime, Color( PINK ),'1', MyVector( 0, 0, 47400 ) ) );
	//VENUS
	mOrbs.push_back( new Orb( MyVector( 1.082* pow( 10, 11 ), 0, 0 ), 4.87 * pow( 10, 24 ), mDeltaTime, Color( YELLOW ),'2', MyVector( 0, 0, 35000 ) ) );
	//EARTH
	Orb* earth = new Orb( MyVector( 1.496 * pow( 10, 11 ), 0, 0 ), 5.976 * pow( 10, 24 ), mDeltaTime, Color( BLUE ),'3', MyVector( 0, 0, 29800 ) );
	mOrbs.push_back( earth ); //v = 29800
	//Moon
	mOrbs.push_back( new Orb( MyVector( 1.496 * pow( 10, 11 ) + 3.78 * pow( 10, 5 ), 0, 0 ), 7.342 * pow( 10, 22 ), mDeltaTime, Color( MAGENTA ),'m', MyVector( 0, 0, 1022 ), earth ) ); //v=1022
	
	//MARS
	mOrbs.push_back( new Orb( MyVector( 2.279*pow( 10, 11 ), 0, 0 ), 6.42*pow(10,23), mDeltaTime, Color( RED ), '4', MyVector( 0, 0, 24100 ) ) );
	//JUPITER
	mOrbs.push_back( new Orb( MyVector( 7.786 * pow( 10, 11 ), 0, 0 ), 1.8986 * pow( 10, 27 ), mDeltaTime, Color( RED ),'5', MyVector( 0, 0, 131000 ) ) );
	//SATURN
	mOrbs.push_back( new Orb( MyVector( 1.433* pow( 10, 12 ), 0, 0 ), 5.69* pow(10,26), mDeltaTime, Color( YELLOW ),'6', MyVector( 0, 0, 9600 ) ) );
	//URANUS
	mOrbs.push_back( new Orb( MyVector( 2.873*pow(10,12), 0, 0 ), 8.68* pow( 10, 25 ), mDeltaTime, Color( GREEN ),'7', MyVector( 0, 0, 6800 ) ) );
	//NEPTUNE
	mOrbs.push_back( new Orb( MyVector( 4.495*pow(10,12), 0, 0 ), 1.03* pow( 10, 26 ), mDeltaTime, Color( CYAN ),'8', MyVector( 0, 0, 5400 ) ) );
	//PLUTO
	mOrbs.push_back( new Orb( MyVector( 5.906 * pow( 10, 12 ), 0, 0 ), 1.46*pow(10,22), mDeltaTime, Color( PINK ),'9', MyVector( 0, 0, 4740 ) ) );
}

void SolarSystem::update( DemoHandler* dh )
{	
	if( dh->keyTyped( 'p' ) )
	{
		mPaused = !mPaused;
	}
	if( dh->keyTyped( 'd' ) )
	{
		mDebug = !mDebug;
	}

	if( !mPaused )
	{
		int limit = mOrbs.size();
		for( int j = 0; j < 365*24*30; j++ )
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
		if( r.length() > 1000 )
		{
			double force = mG* one->getMass() * two->getMass()
				/ ( r.length()
				* r.length() );

			r.normalize();

			one->addForce( r * -force );
			two->addForce( r *  force );
		}
	}
}