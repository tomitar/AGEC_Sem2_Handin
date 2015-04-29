#include "GameScreenGameLevel1.h"
#include "GameObject.h"
#include "Player.h"
#include "Camera.h"
#include "Dodgeball.h"
#include <sstream>

#include <iostream>
using namespace::std;
lighting mLight;

GameScreenGameLevel1::GameScreenGameLevel1()
{
	cout << "GSLV1 constructor" << endl;
	debugPlayer = new Player();
	debugPlayer->SetPosition(Vector3D(-29, 0, 30));

	//AddObjectToArray(debugPlayer, 0);

	mCamera->setPosition(Vector3D(0.0f, 80.0f, 0.0f));
	mCamera->setRotation(Vector3D(90, 0, 0));
	mCamera->setIsStatic(true);

	SetVictoryFlag(false);
	timeSinceStart = 0.0f;

	courtTexture = new Texture();
	courtTexture->Load("Ship_1_Texture.raw", 512, 512);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	mLight = {
		{ 0.5f, 0.5f, 0.5f, 1.0f },
		{ 0.7f, 0.7f, 0.7f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 1.0f }
	};
	
	for (int i = 0; i < 30; i++)
	{
		theDodgeballs.push_back(new Dodgeball());
	}
}

GameScreenGameLevel1::~GameScreenGameLevel1()
{
}

void GameScreenGameLevel1::Render()
{
	GameScreen::Render();
	float light_pos[] = { 0.0f, 50.0f, 0.0f, 1.0f };
	//float light_pos[] = { 0.0f, 20.0f, 0.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, mLight.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, mLight.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, mLight.specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	debugPlayer->Render();
	
	for (int i = 0; i < theDodgeballs.size(); i++)
	{
		theDodgeballs[i]->Render();
	}

	std::stringstream ss;
	ss << debugPlayer->GetLives() << " " << timeSinceStart << "s " << std::endl;
	PrintStringToScreen(10.0f, 80.0f, ss.str());

	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glScalef(1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, courtTexture->GetID());
	DrawCourt();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void GameScreenGameLevel1::Update(float deltaTime, SDL_Event e)
{
	timeSinceStart += deltaTime;
	GameScreen::Update(deltaTime, e);
	debugPlayer->Update(deltaTime, e);
	if (timeSinceStart > 5.0f)
	{
		for (int i = 0; i < theDodgeballs.size(); i++)
		{

			theDodgeballs[i]->Update(deltaTime, e);

			if (theDodgeballs[i]->PositionCheck() == false)
			{
				delete theDodgeballs[i];
				theDodgeballs[i] = new Dodgeball();
			}

			Collision::SphereSphereCollision(theDodgeballs[i]->GetBoundingSphere(), debugPlayer->GetBoundingSphere());

			if (theDodgeballs[i]->GetBoundingSphere()->GetCollided() == true)
			{
				if (theDodgeballs[i]->GetHasHitPlayer() != true)
				{
					debugPlayer->TakeDamage(20);
				}
				switch (debugPlayer->GetLives())
				{
				case 2:
					theDodgeballs[i]->SetPositionOffset(Vector3D(5.0f,0.0f,0.0f));
					break;
				case 1:
					theDodgeballs[i]->SetPositionOffset(Vector3D(5.0f, 0.0f, 5.0f));
					break;
				case 0:
					theDodgeballs[i]->SetPositionOffset(Vector3D(5.0f, 0.0f, -5.0f));
					break;
				}
				theDodgeballs[i]->SetHasHitPlayer(true);
				theDodgeballs[i]->SetParentPlayer(debugPlayer);
			}
		}
	}
	
	if (debugPlayer->GetLives() < 0)
	{
		SetGameOverFlag(true);
	}

	if (debugPlayer->GetPosition().x > 22 && debugPlayer->GetPosition().z < -33)
	{
		SetVictoryFlag(true);
		SetLevelScore(2000 - timeSinceStart);
	}
}

void GameScreenGameLevel1::DrawCourt()
{
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-28.0f, 0.0f, -40.0f);
		//glVertex3f(-5.5f, 0.0f, -5.5f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-28.0f, 0.0f, 33.0f);
		//glVertex3f(5.5f, 0.0f, -5.5f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(28.0f, 0.0f, 33.0f);
		//glVertex3f(5.5f, 0.0f, 5.5f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(28.0f, 0.0f, -40.0f);
		//glVertex3f(-5.5f, 0.0f, 5.5f);
	glEnd();
}