#include "GameScreenLevel3.h"
#include "../gl/glut.h"
#include "ModelLoader.h"
#include "Object3DS.h"

GameScreenLevel3::GameScreenLevel3() : GameScreen()
{
	m3DSModel = new Object3DS(Vector3D(0.0f, 0.0f, 0.0f), "Ship_1_Unwrap.3ds", true, "Ship_1_Texture.raw");

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	mLight = {
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 0.7f, 0.7f, 0.7f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 1.0f }
	};
}

GameScreenLevel3::~GameScreenLevel3()
{
}

void GameScreenLevel3::Render()
{
	SetLight();

	GameScreen::Render();

	m3DSModel->render(GL_TEXTURE_2D);
}

void GameScreenLevel3::Update(float deltaTime, SDL_Event e)
{
	GameScreen::Update(deltaTime, e);

	m3DSModel->update(deltaTime, e, ANIM_STRAFE);

	mCurrentTime += deltaTime;
}

void GameScreenLevel3::SetLight()
{
	float light_Pos[] = { 50.0f, 50.0f, 50.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_Pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, mLight.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, mLight.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, mLight.specular);
}