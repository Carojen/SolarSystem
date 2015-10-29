#pragma once
#include <string>
using namespace std;

class DemoHandler;

/*
	This is the abstract base-class for demos. A descendant class
	Will implement the update-method which is called each frame by the demoHandler.
	Use the provided DemoHandler-object to draw and to read mouse and key events.
	Don't forget to add your demo in the Main.cpp-file.
*/

class Demo
{
public:
	virtual void update(DemoHandler*) = 0;
	const virtual string getName()
	{
		return "Solar System";
	}
	const virtual string getInfo()
	{
		return " \nPlease describe your work by returning a description from the \"getInfo\"-method\n\nThank you!\n";
	}
};


/*
	(c)2009 Henrik Engström, henrik.engstrom@his.se
	This code may only be used by students in the Game Physics course at the University of Skövde 
	Contact me if you want to use it for other purposes.
*/