#include "GameScreenMenu.h"

GameScreenMenu::GameScreenMenu()
{
}

GameScreenMenu::~GameScreenMenu()
{
}

void GameScreenMenu::Update(float deltaTime, SDL_Event e)
{
	GameScreen::Update(deltaTime,e);
}

void GameScreenMenu::Render()
{
	GameScreen::Render();

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

	PrintStringToScreen(50, 60, "YOU MUST MOVE FROM THE LEFT SIDE OF THE COURT TO THE RIGHT");
	PrintStringToScreen(50, 50, "USE THE ARROW KEYS TO DODGE BALLS BEING THROWN AT YOU");
	PrintStringToScreen(50, 40, "IF YOU ARE HIT BY 3 BALLS, YOU'RE OUT!");
	PrintStringToScreen(50, 20, "PRESS RETURN TO CONTINUE");

	glDisable(GL_COLOR);
	glEnable(GL_LIGHTING);

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void GameScreenMenu::PrintStringToScreen(int xpos, int ypos, string inString)
{
	xpos = 50 - (inString.size() / 2);
	glRasterPos2i(xpos, ypos);
	for (int i = 0; i < inString.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)inString[i]);
	}
}