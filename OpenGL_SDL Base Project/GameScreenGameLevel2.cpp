#include "GameScreenGameLevel2.h"
#include "Camera.h"

GameScreenGameLevel2::GameScreenGameLevel2()
{
	level2Player = new Player(MV_FPS);
	level2Player->SetPosition(Vector3D(0, 3, 0));
}


GameScreenGameLevel2::~GameScreenGameLevel2()
{
}

void GameScreenGameLevel2::Render()
{
	GameScreen::Render();
	DrawGround(-1.0f);
}

void GameScreenGameLevel2::Update(float deltaTime, SDL_Event e)
{
	GameScreen::Update(deltaTime, e);
	mCamera->setPosition(level2Player->GetPosition());
	mCamera->setRotation(level2Player->GetRotation());
	level2Player->Update(deltaTime, e);
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