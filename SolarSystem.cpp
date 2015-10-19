#include "SolarSystem.h"

SolarSystem::SolarSystem()
{
	mOrbs.push_back( new Orb(MyVector(0,0,0), 1000, 0, Color(YELLOW)));
	mOrbs.push_back( new Orb( MyVector( 5, 0, 0 ), 500, 0, Color( BLUE ) ) );
}

void SolarSystem::update( DemoHandler* dh )
{
	for( unsigned int i = 0; i < mOrbs.size() - 2; i++ )
	{
		addForce( mOrbs[i], mOrbs[i + 1] );
	}

	for each( Orb* o in mOrbs )
	{
		o->update( mDeltaTime );
	}
	draw( dh );
}

void SolarSystem::draw( DemoHandler* draw )
{
	for each( Orb* o in mOrbs )
	{
		o->draw(draw);
	}
}

void SolarSystem::addForce( Orb* one, Orb* two )
{
	//Add gravity calculations
	// F = G* m1*m2/dist^2
	// mG* one->getMass * two->getMass / ( (one->getPosition() - two->getPosition()) * (one->getPosition() - two->getPosition()));
}