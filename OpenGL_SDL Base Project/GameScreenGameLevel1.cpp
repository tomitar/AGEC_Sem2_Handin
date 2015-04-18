#include "GameScreenGameLevel1.h"
#include "GameObject.h"
#include "Player.h"
#include "Camera.h"

#include <iostream>
using namespace::std;
lighting mLight;

GameScreenGameLevel1::GameScreenGameLevel1()
{
	cout << "GSLV1 constructor" << endl;
	debugPlayer = new Player();
	//AddObjectToArray(debugPlayer, 0);
	mCamera->setPosition(Vector3D(0.0f, 80.0f, 0.0f));
	mCamera->setRotation(Vector3D(90, 0, 0));
	mCamera->setIsStatic(true);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	mLight = {
		{ 0.5f, 0.5f, 0.5f, 1.0f },
		{ 0.7f, 0.7f, 0.7f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 1.0f }
	};
}

GameScreenGameLevel1::~GameScreenGameLevel1()
{
}

void GameScreenGameLevel1::Render()
{
	GameScreen::Render();
	float light_pos[] = { 0.0f, 50.0f, 150.0f, 1.0f };
	//float light_pos[] = { 0.0f, 20.0f, 0.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, mLight.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, mLight.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, mLight.specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	debugPlayer->Render();
}

void GameScreenGameLevel1::Update(float deltaTime, SDL_Event e)
{
	GameScreen::Update(deltaTime, e);
	debugPlayer->Update(deltaTime, e);
}