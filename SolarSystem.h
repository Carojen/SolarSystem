#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H
#include "SF_src/Demo.h"
#include "Orb.h"
#include <vector>

class SolarSystem: public Demo
{
public:
	SolarSystem();

	void update( DemoHandler* dh );
	void draw( DemoHandler* draw );
	void addForce( Orb* one, Orb* two );
//private:
	void calc();
	std::vector<Orb*> mOrbs;
	double mG;
	double mDeltaTime;
	bool mPaused;
};
#endif