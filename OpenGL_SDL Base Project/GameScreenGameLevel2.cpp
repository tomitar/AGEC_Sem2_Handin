#include "GameScreenGameLevel2.h"
#include "Camera.h"
#include "Constants.h"
#include <sstream>

GameScreenGameLevel2::GameScreenGameLevel2()
{
	level2Player = new Player(MV_FPS);
	level2Player->SetPosition(Vector3D(0, 3, 0));
	level2Terrain = new Terrain();
	level2Terrain->Initialise();

	targetTime = 0.0f;
	waveNumber = 0;
	hitTargets = 0;

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	mLight = {
		{ 0.0f, 0.0f, 0.0f, 1.0f },
		{ 0.7f, 0.7f, 0.7f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 1.0f }
	};

	TargetWave();
}


GameScreenGameLevel2::~GameScreenGameLevel2()
{
}

void GameScreenGameLevel2::Render()
{
	GameScreen::Render();

	float light_pos[] = { 0.0f, 1000.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, mLight.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, mLight.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, mLight.specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	
	level2Terrain->Render();
	DrawGround(-1.0f);

	for (int i = 0; i < theTargets.size(); i++)
	{
		if (theTargets[i] != NULL)
		{
			theTargets[i]->Render();
		}
	}

	for (int i = 0; i < thePowerups.size(); i++)
	{
		if (thePowerups[i] != NULL)
		{
			if (thePowerups[i]->GetHasActive() == false)
			{
				thePowerups[i]->Render();
			}
		}
	}

	int targetsLeft = 0;
	targetsLeft = theTargets.size() - hitTargets;
	std::stringstream ss;
	ss << "WAVE TIME: " << targetTime << "s" << std::endl;
	PrintStringToScreen(10.0f, 90.0f, ss.str());
	ss.str(std::string());
	ss << "WAVE NUMBER: " << waveNumber << std::endl;
	PrintStringToScreen(10.0f, 95.0f, ss.str());
	ss.str(std::string());
	ss << "TARGETS LEFT: " << targetsLeft << std::endl;
	PrintStringToScreen(10.0f, 97.5f, ss.str());
	if (level2Player->GetMyPowerup() != NULL)
	{
		ss.str(std::string());
		ss << "POWERUP: " << level2Player->GetMyPowerup() << std::endl;
		PrintStringToScreen(10.0f, 30.5f, ss.str());
	}
}

void GameScreenGameLevel2::Update(float deltaTime, SDL_Event e)
{
	for (int i = 0; i < thePowerups.size(); i++)
	{
		if (thePowerups[i] != NULL)
		{
			thePowerups[i]->Update(deltaTime, e);

			if (thePowerups[i]->GetHasActive() == false)
			{
				thePowerups[i]->SetPosition(Vector3D(thePowerups[i]->GetPosition().x,
					(level2Terrain->GetHeight(thePowerups[i]->GetPosition().x,
					thePowerups[i]->GetPosition().z)
					+ 3.0f),
					thePowerups[i]->GetPosition().z));

				Collision::SphereSphereCollision(thePowerups[i]->GetBoundingSphere(), level2Player->GetBoundingSphere());

				if (thePowerups[i]->GetBoundingSphere()->GetCollided() == true)
				{
					level2Player->SetMyPowerup(thePowerups[i]->GetPType());
					thePowerups[i]->SetHasActive(true);
				}
			}
			else
			{
				if (thePowerups[i]->GetHasFinished() == true)
				{
					delete thePowerups[i];
					thePowerups[i] = NULL;
					level2Player->SetMyPowerup(PT_NONE);
				}
			}
		}
	}

	targetTime = targetTime - deltaTime;
	if (targetTime < 0.0f)
	{
		SetGameOverFlag(true);
	}

	GameScreen::Update(deltaTime, e);

	mCamera->setPosition(Vector3D(	level2Player->GetPosition().x,
									level2Player->GetPosition().y +2.0f,
									level2Player->GetPosition().z));
	mCamera->setRotation(level2Player->GetRotation());
	level2Player->Update(deltaTime, e);
	level2Terrain->Update(deltaTime);
	level2Player->SetPosition(Vector3D(	level2Player->GetPosition().x,
										level2Terrain->GetHeight(	level2Player->GetPosition().x,
																	level2Player->GetPosition().z),
										level2Player->GetPosition().z));

	for (int i = 0; i < theTargets.size(); i++)
	{
		if (theTargets[i] != NULL)
		{
			theTargets[i]->Update(deltaTime, e);
			theTargets[i]->SetPosition(Vector3D(theTargets[i]->GetPosition().x,
				(level2Terrain->GetHeight(theTargets[i]->GetPosition().x,
				theTargets[i]->GetPosition().z)
				+ 3.0f),
				theTargets[i]->GetPosition().z));

			Collision::SphereSphereCollision(theTargets[i]->GetBoundingSphere(), level2Player->GetBoundingSphere());
			if (theTargets[i]->GetBoundingSphere()->GetCollided() == true)
			{
				delete theTargets[i];
				theTargets[i] = NULL;
				hitTargets++;
				AddLevelScore(25.0f);
			}
		}
	}
	
	if (hitTargets == theTargets.size())
	{
		TargetWave();
	}
}

void GameScreenGameLevel2::DrawGround(float groundLevel)
{
	float extent = 600.0f;
	float stepSize = 20.0f;

	glEnable(GL_COLOR);

	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_LINES);
	for (int i = -extent; i < extent; i += stepSize)
	{
		glVertex3f(i, groundLevel, extent);
		glVertex3f(i, groundLevel, -extent);

		glVertex3f(-extent, groundLevel, i);
		glVertex3f(extent, groundLevel, i);
	}
	glEnd();

	glDisable(GL_COLOR);
}

void GameScreenGameLevel2::TargetWave()
{
	AddLevelScore(50.0f + targetTime);
	int waveTotal;
	targetTime = WAVE_TIME;

	for (int i = 0; i < theTargets.size(); i++)
	{
		delete theTargets[i];
		theTargets[i] = NULL;
	}

	for (int i = 0; i < thePowerups.size(); i++)
	{
		delete thePowerups[i];
		thePowerups[i] = NULL;
	}

	switch (waveNumber)
	{

	case 0:
		waveTotal = WAVE_1;
		targetTime *= 1.0f;
		for (int i = 0; i < waveTotal; i++)
		{
			theTargets.push_back(new Target());
		}
		break;

	case 1:
		waveTotal = WAVE_2;
		targetTime *= 2.0f;
		for (int i = 0; i < waveTotal; i++)
		{
			theTargets.push_back(new Target());
		}
		break;

	case 2:
		waveTotal = WAVE_3;
		targetTime *= 3.0f;
		for (int i = 0; i < waveTotal; i++)
		{
			theTargets.push_back(new Target());
		}
		break;

	case 3:
		SetVictoryFlag(true);
		AddLevelScore(200.0f);
		break;
	}

	waveNumber++; 
	hitTargets = 0;

	for (int i = 0; i < 3; i++)
	{
		thePowerups.push_back(new Powerup());
	}
}