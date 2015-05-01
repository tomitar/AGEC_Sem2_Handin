#include "GameScreenLevel1.h"
#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include "Constants.h"
#include "Commons.h"
#include <iostream>

using namespace::std;

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::GameScreenLevel1() : GameScreen()
{
	mTerrain.Initialise();

	if (m_p3DSModel = new Object3DS(Vector3D(20.0f, 20.0f, 20.0f), "Tree_1.3ds", true, "treeTexture_1"))
	{
		std::cout << "Model loaded correctly." << std::endl;
	}

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	mLight = {
		{ 0.0f, 0.0f, 0.0f, 1.0f },
		{ 0.7f, 0.7f, 0.7f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 1.0f }
	};
}

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::~GameScreenLevel1()
{	
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::Render()
{
	//Parent class deals with camera.
	GameScreen::Render();

	SetLight();

	//Draw the terrain.
	mTerrain.Render();

	m_p3DSModel->render(GL_FILL);
}

void GameScreenLevel1::SetLight()
{
	float light_pos[] = { 0.0f, 50.0f, 150.0f, 1.0f };
	//float light_pos[] = { 0.0f, 20.0f, 0.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, mLight.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, mLight.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, mLight.specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//Call parent update for camera functionality.
	GameScreen::Update(deltaTime, e);

	m_p3DSModel->update(deltaTime, e, ANIM_CUSTOM, Vector3D(0.0f,mTerrain.GetHeight(0,0),0.0f));

	mTerrain.Update(deltaTime);

	mCurrentTime += deltaTime;
}

//--------------------------------------------------------------------------------------------------