#include "SolarSystem.h"

SolarSystem::SolarSystem()
{
	mG = 6.6743 * pow( 10, -11 );
	mDeltaTime = 1.0 ;

	mOrbs.push_back( new Orb( MyVector( 0, 0, 0 ), 1.98855 * pow(10,30), mDeltaTime,Color( YELLOW )));
	mOrbs.push_back( new Orb( MyVector( 5.79 * pow( 10, 10 ), 0, 0 ), 3.3011 * pow( 10, 23 ), mDeltaTime, Color( GRAY ) ) );
	mOrbs.push_back( new Orb( MyVector( 1.082* pow( 10, 11 ), 0, 0 ), 4.87 * pow(10,24), mDeltaTime, Color( GRAY ) ) );
	
	mOrbs.push_back( new Orb( MyVector( 1.496 * pow( 10, 11), 0, 0 ), 5.976 * pow( 10, 24 ), mDeltaTime, Color( BLUE ) ) );
	mOrbs.push_back( new Orb( MyVector( 7.786 * pow(10,11), 0, 0 ), 1.8986 * pow( 10, 27 ), mDeltaTime, Color( RED ) ) );
	mOrbs.push_back( new Orb( MyVector( 5.906 * pow(10,12), 0, 0 ), 1.8986 * pow( 10, 27 ), mDeltaTime, Color( PINK ) ) );


}

void SolarSystem::update( DemoHandler* dh )
{	
	for( int j = 0; j < 365*24; j++ )
	{
		for( unsigned int i = 0; i < mOrbs.size() - 1 ; i++ )
		{
			for( unsigned int k = i+1; k < mOrbs.size(); k++ )
			{
				addForce( mOrbs[i], mOrbs[k] );
			}			
		}

		for each( Orb* o in mOrbs )
		{
			o->update( mDeltaTime );
		}
	}	
	draw( dh );
}

void SolarSystem::draw( DemoHandler* draw )
{
	
	for each( Orb* o in mOrbs )
	{
		MyVector test = o->getPosition();
		o->draw(draw);
	}
}

void SolarSystem::addForce( Orb* one, Orb* two )
{
	if( ( one->getPosition() - two->getPosition() ).length() > 100 )
	{
		double force = mG* one->getMass( ) * two->getMass( )
			/ ( ( one->getPosition( ) - two->getPosition( ) ).length( )
			* ( one->getPosition( ) - two->getPosition( ) ).length( ) );

		MyVector axis = one->getPosition( ) - two->getPosition( );
		axis.normalize( );

		one->addForce( axis * -force );
		two->addForce( axis *  force );
	}
	//else add mass to largest object and remove the other
}