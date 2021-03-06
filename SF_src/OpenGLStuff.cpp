#include <math.h>
#include <iostream>
#include "DemoHandler.h"
#ifdef _WIN32
#include "glut.h"
#include <algorithm>
#else
#include <GLUT/glut.h>
#endif
using namespace std;
#include <sstream>


/*
	You should not need to change or use the content of this file.
*/

static const int GRIDWIDTH = 50;

struct Globals
{
	float cameraAngle,cameraAngleDelta;//Camera control
	float cameraHeight,cameraHeightDelta;//Camera control
	float cameraRadius,cameraRadiusDelta;//Camera control
	bool grid;//draw grid
	bool snap;//snap to grDid
	bool fullscreen;//draw fullscreen
	bool showOutput;//show console
	View view;//which view we should use

	int screenW,screenH;//the screen size in pixels
	int verticalGrids,horizontalGrids;//the number of grids that fits in the window

	GLUquadric *quadric;
};

struct Globals global;

void toggleFullscreen()
{
		global.fullscreen = !global.fullscreen;
		if(global.fullscreen)
			glutFullScreen();
		else
		{
			glutReshapeWindow(800,600);
			glutPositionWindow(100,200);
		}
}


void drawGrid()
{	
	if(global.view == PERSPECTIVE)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_BLEND);
	    glDepthMask(GL_FALSE);
		glBlendFunc(GL_SRC_ALPHA,  GL_ONE_MINUS_SRC_ALPHA);
	}else
		glDisable(GL_LIGHTING);
   

   float alpha = 0.5;
   glLineWidth(1);
   if(global.snap)
   {
		alpha = 0.8;
	    glLineWidth(2);
   }

   
    glColor4d(1,1,1,1);
	GLfloat diffuseMaterial[]  =  { 1, 0,0, alpha };
	GLfloat mat_specular[]  =  { 0.8, 0.8, 0.8, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

	const int DIM = min(global.verticalGrids,global.horizontalGrids)-2;
	if(global.view != PERSPECTIVE)
	   glColor4f(1,0,0,1);

	glBegin(GL_LINES);
	glNormal3d(0,0,1);
	for(int i = 0;i <= DIM;i++)
	{	
		glVertex3d(0,i,0);glVertex3d(DIM,i,0);glVertex3d(i,0,0);glVertex3d(i,DIM,0);
    }
    glEnd();
   
    diffuseMaterial[0] = 0;diffuseMaterial[1] = 1;
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuseMaterial);
    if(global.view != PERSPECTIVE)
	   glColor4f(0,1,0,1);
	glBegin(GL_LINES);
	glNormal3d(1,0,0);
	for(int i = 0;i<= DIM;i++)
	{
	   glVertex3d(0,i,0);glVertex3d(0,i,DIM); glVertex3d(0,0,i);glVertex3d(0,DIM,i);
    }
    glEnd();


	diffuseMaterial[1] = 0;diffuseMaterial[2] = 1;
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuseMaterial);
   	if(global.view!= PERSPECTIVE)
		glColor4f(0,0,1,1);
	glBegin(GL_LINES);
	glNormal3d(0,1,1);
	for(int i = 0;i<= DIM;i++)
	{
	    glVertex3d(0,0,i);glVertex3d(DIM,0,i);glVertex3d(i,0,0);glVertex3d(i,0,DIM);
	}
    glEnd();
    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
}

void initScene()
{
	glViewport(0, 0, global.screenW, global.screenH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	Point camera = Point(global.cameraRadius*sin(global.cameraAngle),global.cameraHeight,global.cameraRadius*cos(global.cameraAngle));

	if(global.view == PERSPECTIVE)
	{		
		gluPerspective(45.0f, float(global.screenW) / float(global.screenH), 0.1f, 500.0f);   // Skapar en projektionsmatris
		gluLookAt(camera.mX,camera.mY,camera.mZ, 0, 0, 0, 0, 1, 0); 
	}
	else
	{
		glOrtho(0,1.0*global.screenW/GRIDWIDTH,0,1.0*global.screenH/GRIDWIDTH,-100,100); 
		if(global.view == XY_PLANE)
			gluLookAt(-1, -1, 1, -1, -1, 0, 0, 1, 0);   
		else if(global.view == ZY_PLANE)
			gluLookAt(-1, -1, -1, 0, -1, -1, 0, 1, 0); 
		else
			gluLookAt(-1, 1, -1, -1, 0, -1, 1, 0, 0);    
	}	 

    glMatrixMode(GL_MODELVIEW);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);   
	glLoadIdentity();

		

	GLfloat LightAmbient[] =   { 0.2f, 0.2f, 0.2f, 1.0f }; 
	GLfloat LightDiffuse[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat LightSpecular[] = {1.0, 1.0, 1.0, 1.0};
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);
	
	GLfloat light_position[]  =  { 8, 8, 20 ,0};
	
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	glEnable(GL_LIGHT1);

	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glDepthMask(GL_TRUE);
}


int previousTime = -1;

void display()
{
    if(previousTime<0){
        previousTime = glutGet(GLUT_ELAPSED_TIME);
        return;
    }
    int now = glutGet(GLUT_ELAPSED_TIME);
    if(now-previousTime<16)//60FPS
        return;
    previousTime+= 16;
    if(previousTime<now)
    {
        //cout<<"Lag: "<<(now-previousTime)<<endl;
        previousTime=now;//Vi vill inte få problem när programmet pausar
    }
	initScene();
	GLfloat diffuseMaterial[]  =  { 1,1,1, 1.0 };
	GLfloat mat_specular[]  =  { 0.4, 0.4, 0.4, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 15.0);
	DemoHandler::inst().update();
	if(global.grid)
		drawGrid();
	if(global.showOutput)
		DemoHandler::inst().printConsole(global.screenW,global.screenH);
	glutSwapBuffers();
}
void showHelp()
{
	DemoHandler::inst().addMessage("1-9 toggles planets. (number) 0 toggles sun, m toggles moon.");
	DemoHandler::inst().addMessage("P pauses and unpauses simulation. Change speed with +/-.");
	DemoHandler::inst().addMessage("Press D for debug lines (blue: direction from previous position, red: direction of total force influence)");
	DemoHandler::inst().addMessage("Press (letter) O while in debug mode to get output values in console.");
}

void timer(int timeout)
{
	glutTimerFunc(timeout, timer, timeout);   // Vi mÂste starta om timern varje gÂng
	
	global.cameraAngle +=  global.cameraAngleDelta;
	global.cameraHeight +=  global.cameraHeightDelta;
	global.cameraRadius +=  global.cameraRadiusDelta;
	if(global.cameraRadius<= 0)
		global.cameraRadius = 0.0001;
    
    
}
void specialDown(int key,int x,int y)
{
	if(global.view!= PERSPECTIVE)
		return;
		
	bool shift = glutGetModifiers() == GLUT_ACTIVE_SHIFT;
	switch(key)
	{
		case GLUT_KEY_LEFT:
			global.cameraAngleDelta  =  -0.04;
			break;
		case GLUT_KEY_RIGHT:
			global.cameraAngleDelta  =  0.04;
			break;
		case GLUT_KEY_PAGE_UP:
			global.cameraHeightDelta  =  0.4;
			break;
		case GLUT_KEY_PAGE_DOWN:
			global.cameraHeightDelta  =  -0.4;
			break;
		case GLUT_KEY_UP:
			if(shift)
				global.cameraHeightDelta  =  0.4;//if pg_up is missing
			else
				global.cameraRadiusDelta  =  -0.4;
			break;
		case GLUT_KEY_DOWN:
			if(shift)
				global.cameraHeightDelta  =  -0.4;//if pg_down is missing
			else
				global.cameraRadiusDelta  =  0.4;
			break;
	}
}
void specialUp(int key, int x, int y) 
{	
	bool shift = glutGetModifiers() == GLUT_ACTIVE_SHIFT;
	int idx = key-GLUT_KEY_F1;
	if(shift&&idx>= 0&&idx<13)
	{
		
		if(idx<DemoHandler::inst().getDemoCnt())
		{
			DemoHandler::inst().setActive(idx);
		}
	}
	else
	{
		switch (key) 
		{	
			case GLUT_KEY_F1:
				global.view = XY_PLANE;
				break;
			case GLUT_KEY_F2:
				DemoHandler::inst().setView(ZY_PLANE);
				global.view = ZY_PLANE;
				break;
			case GLUT_KEY_F3:
  				DemoHandler::inst().setView(ZX_PLANE);
				global.view = ZX_PLANE;
				break;
			case GLUT_KEY_F4:
				global.view = PERSPECTIVE;
				break;				
			case GLUT_KEY_F9:
				toggleFullscreen();
				break;		
			case GLUT_KEY_F10:
				global.grid = !global.grid;
				break;		
			case GLUT_KEY_F11:
				global.snap = !global.snap;
				break;		
			case GLUT_KEY_F12:
				global.showOutput = !global.showOutput;
				break;		
			case GLUT_KEY_HOME:
				global.showOutput = true;
				showHelp();				
				break;		
			case GLUT_KEY_LEFT:
			case GLUT_KEY_RIGHT:
				global.cameraAngleDelta = 0;
			break;
			case GLUT_KEY_PAGE_UP:
			case GLUT_KEY_PAGE_DOWN:
				global.cameraHeightDelta = 0;
			break;
			case GLUT_KEY_UP:
			case GLUT_KEY_DOWN:
				global.cameraHeightDelta = 0;
				global.cameraRadiusDelta = 0;
			break;
		}
	}
    DemoHandler::inst().setView(global.view);

}

void keyboardUp(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 27:   
			exit(0);  
		break;
	}
	global.cameraRadiusDelta  =  0.0;//To handle a strange bugg on mac that generates special key down but ordinary key up for e.g. 'd'
	global.cameraAngleDelta = 0;
	global.cameraHeightDelta = 0;
	DemoHandler::inst().setKeyTyped(key);
}

void mouseMove(int x,int y)
{
	float p1 = (x-GRIDWIDTH)/((float)GRIDWIDTH);
	float p2 = (global.screenH-y-GRIDWIDTH)/((float)GRIDWIDTH);
	if(global.snap)
	{
		p1 = (int)(p1 + (p1 > 0.0 ? +0.5: -0.5));
		p2 = (int)(p2 + (p2 > 0.0 ? +0.5: -0.5));
	}
	if(global.view == XY_PLANE)	
		DemoHandler::inst().setMousePos(p1,p2,0);
	else if(global.view == ZY_PLANE)
		DemoHandler::inst().setMousePos(0,p2,p1);	
	else if(global.view == ZX_PLANE)
		DemoHandler::inst().setMousePos(p2,0,p1);	
}

void mouseClick(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON)
	{
		if(state == GLUT_UP)
			DemoHandler::inst().setMouseClick(LEFT);
		DemoHandler::inst().setMouseState(LEFT,(state == GLUT_DOWN));	
	}
	if(button == GLUT_MIDDLE_BUTTON)
	{
		if(state == GLUT_UP)	
			DemoHandler::inst().setMouseClick(MIDDLE);
		DemoHandler::inst().setMouseState(MIDDLE,(state == GLUT_DOWN));	
	}
	if(button == GLUT_RIGHT_BUTTON)
	{
		if(state == GLUT_UP)
			DemoHandler::inst().setMouseClick(RIGHT);
		DemoHandler::inst().setMouseState(RIGHT,(state == GLUT_DOWN));	
	}
}

void reshape(int width, int height)
{
	global.screenW = width;
	global.screenH = height;	
	global.verticalGrids = width/GRIDWIDTH;
	global.horizontalGrids = height/GRIDWIDTH;

}
void myMenu(int val)
{
	exit(0);
}
void demosMenu(int val)
{
	if(val<DemoHandler::inst().getDemoCnt())
		DemoHandler::inst().setActive(val);
}
void myViewMenu(int val)
{
	switch(val)
	{
		case 100:
			global.view = XY_PLANE;
			break;
		case 110:
			global.view = ZY_PLANE;
			break;
		case 120:
			global.view = ZX_PLANE;
			break;
		case 130:
			global.view = PERSPECTIVE;
			break;

	}

}
void mySettingsMenu(int val)
{
	switch(val)
	{
		case 1000:
			toggleFullscreen();
			break;
		case 1010:
			global.grid = !global.grid;
			break;
		case 1020:
			global.snap = !global.snap;
			break;
		case 1030:
			global.showOutput = !global.showOutput;
			break;
		case 1040:
			global.showOutput = true;
			showHelp();
			break;
		case 1050:
			global.cameraAngle = 0.5;
			global.cameraHeight = 8;
			global.cameraRadius = 16;
			break;
	}
}

void idle()
{
	glutPostRedisplay();   
}


void start(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);   // Vi vill ha dubbelbuffring och z-buffer (depth buffer)
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 200);

	glutCreateWindow("Spelfysik");
	global.cameraAngle = 0.5;
	global.cameraHeight = 8;
	global.cameraRadius = 16;
	global.grid = true;
	global.snap = false;
	global.fullscreen = false;
	global.showOutput = true;
	global.quadric = gluNewQuadric();
	global.view = XY_PLANE;

	showHelp();

	glutTimerFunc(1000/60, timer, 1000/60);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardUpFunc(keyboardUp);
    
	glutSpecialFunc(specialDown);
	glutSpecialUpFunc(specialUp);
	glutMouseFunc(mouseClick);
	glutPassiveMotionFunc(mouseMove);
	glutMotionFunc(mouseMove);

	int settingsId = glutCreateMenu(mySettingsMenu);
	glutAddMenuEntry("Toggle Full-screen (F9)",1000);
	glutAddMenuEntry("Toggle grid (F10)",1010);
	glutAddMenuEntry("Toggle snap (F11)",1020);
	glutAddMenuEntry("Toggle output (F12)",1030);
	glutAddMenuEntry("Show help (HOME)",1040);
	glutAddMenuEntry("Reset perspective view",1050);

	int viewId = glutCreateMenu(myViewMenu);
	glutAddMenuEntry("XY-plane (F1)",100);
	glutAddMenuEntry("ZY-plane (F2)",110);
	glutAddMenuEntry("ZX-plane (F3)",120);
	glutAddMenuEntry("Perspective (F4)",130);


	int demoId = glutCreateMenu(demosMenu);
	for(int i = 0;i<DemoHandler::inst().getDemoCnt();i++)
	{
		stringstream out;
		out<<DemoHandler::inst().getName(i)<<" (shift-F"<<i+1<<")";
		glutAddMenuEntry(out.str().c_str(),i);
	}

	glutCreateMenu(myMenu);
	glutAddSubMenu("Demos",demoId);
	glutAddSubMenu("View",viewId);
	glutAddSubMenu("Settings",settingsId);
	glutAddMenuEntry("Quit (esc)",1020);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}

/*
	(c)2009 Henrik Engström, henrik.engstrom@his.se
	This code may only be used by students in the Game Physics course at the University of Skövde 
	Contact me if you want to use it for other purposes.
*/

