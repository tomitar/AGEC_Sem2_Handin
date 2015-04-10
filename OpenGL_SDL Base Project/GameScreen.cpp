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

	//initialise the gameobject array
	/*for (int i = 0; i < 65; i++)
	{
		ClearArrayLocation(i);
	}*/
}

//--------------------------------------------------------------------------------------------------

GameScreen::~GameScreen()
{
	/*for (int i = 0; i < 65; i++)
	{
		delete gameObjectArray[i];
		ClearArrayLocation(i);
	}*/
	//delete gameObjectArray;
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

//void GameScreen::ClearArrayLocation(int arrayIndex)
//{
//	gameObjectArray[arrayIndex] = NULL;
//}