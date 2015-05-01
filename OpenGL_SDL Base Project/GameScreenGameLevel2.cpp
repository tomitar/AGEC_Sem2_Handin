#include "GameScreenGameLevel2.h"
#include "Camera.h"


GameScreenGameLevel2::GameScreenGameLevel2()
{
	level2Player = new Player(MV_FPS);
	level2Player->SetPosition(Vector3D(0, 3, 0));
	level2Terrain = new Terrain();
	level2Terrain->Initialise();

	targetTime = 0.0f;

	for (int i = 0; i < 15; i++)
	{
		theTargets.push_back(new Target());
	}

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	mLight = {
		{ 0.0f, 0.0f, 0.0f, 1.0f },
		{ 0.7f, 0.7f, 0.7f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 1.0f }
	};
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
		theTargets[i]->Render();
	}
}

void GameScreenGameLevel2::Update(float deltaTime, SDL_Event e)
{
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
		theTargets[i]->Update(deltaTime, e);
		theTargets[i]->SetPosition(Vector3D(theTargets[i]->GetPosition().x,
											(level2Terrain->GetHeight(	theTargets[i]->GetPosition().x,
																		theTargets[i]->GetPosition().z)+5.0f),
											theTargets[i]->GetPosition().z));
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