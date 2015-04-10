#include "GameScreenLevel2.h"
#include "../gl/glut.h"
#include "ModelLoader.h"
#include "Object3DS.h"

GameScreenLevel2::GameScreenLevel2() : GameScreen()
{
	m3DSModel = new Object3DS(Vector3D(0.0f, 0.0f, 0.0f), "Ship_1_Unwrap.3ds", true, "Ship_1_Texture.raw");
	m3DSModel1 = new Object3DS(Vector3D(0.0f, 0.0f, 0.0f), "Walther_PPK.3ds", false, "PPK_Texture.raw");
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	mLight = {
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 0.7f, 0.7f, 0.7f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 1.0f }
	};

	gMaterial = {
		{ 0.2f, 0.2f, 0.2f },
		{ 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0, 1.0f },
		100.0f
	};
}


GameScreenLevel2::~GameScreenLevel2()
{
}


void GameScreenLevel2::Render()
{
	SetLight();

	GameScreen::Render();

	DrawGround(-200.0f);
	DrawGround(200.0f);

	//glutSolidSphere(3.0, 20, 20);

	m3DSModel->render(GL_FILL);
	m3DSModel->render(GL_LINE);
	
	m3DSModel1->render(GL_LINE);
}


void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
	GameScreen::Update(deltaTime, e);

//	m3DSModel->update(deltaTime, e, ANIM_SPIN);
//	m3DSModel1->update(deltaTime, e, ANIM_SPIN);

	mCurrentTime += deltaTime;
}

void GameScreenLevel2::SetLight()
{
	float light_Pos[] = { 50.0f, 50.0f, 50.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_Pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, mLight.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, mLight.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, mLight.specular);
}

void GameScreenLevel2::DrawGround(float groundLevel)
{
	float extent = 600.0f;
	float stepSize = 20.0f;

	glEnable(GL_COLOR_MATERIAL);

	glMaterialfv(GL_FRONT, GL_AMBIENT, gMaterial.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, gMaterial.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, gMaterial.specular);
	glMaterialf(GL_FRONT, GL_SHININESS, gMaterial.shininess);;

	glBegin(GL_LINES);
	for (int i = -extent; i < extent; i += stepSize)
	{
		glVertex3f(i, groundLevel, extent);
		glVertex3f(i, groundLevel, -extent);

		glVertex3f(-extent, groundLevel, i);
		glVertex3f(extent, groundLevel, i);
	}
	glEnd();

	glDisable(GL_COLOR_MATERIAL);
}