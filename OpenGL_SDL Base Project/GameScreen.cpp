#include "GameScreen.h"
#include "../gl/glut.h"
#include "Camera.h"
#include "Constants.h"

//--------------------------------------------------------------------------------------------------

GameScreen::GameScreen()
{
	//Set up the camera.
	mCamera = Camera::GetInstance();

	//OpenGL set up.
	glEnable(GL_CULL_FACE);								//Stop calculation of inside faces
	glEnable(GL_DEPTH_TEST);							//Hidden surface removal

	//clear background colour.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	SetGameOverFlag(false);
	SetLevelScore(0.0f);
}

//--------------------------------------------------------------------------------------------------

GameScreen::~GameScreen()
{
}

//--------------------------------------------------------------------------------------------------

void GameScreen::Render()
{	
	glRenderMode(GL_3D_COLOR_TEXTURE);
	mCamera->Render();

	glRenderMode(GL_2D);
}

//--------------------------------------------------------------------------------------------------

void GameScreen::Update(float deltaTime, SDL_Event e)
{
	mCamera->Update(deltaTime, e);
}

//--------------------------------------------------------------------------------------------------

void GameScreen::ClearArrayLocation(int arrayIndex)
{
	gameObjectArray[arrayIndex] = NULL;
}

//--------------------------------------------------------------------------------------------------

void GameScreen::PrintStringToScreen(int xpos, int ypos, string inString)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);

	glDisable(GL_LIGHTING);
	glEnable(GL_COLOR);
	glColor3f(0.8f, 0.8f, 0.8f);

	xpos = 50 - (inString.size() / 2);
	glRasterPos2i(xpos, ypos);
	for (int i = 0; i < inString.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)inString[i]);
	}

	glDisable(GL_COLOR);
	glEnable(GL_LIGHTING);

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}