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

	PrintStringToScreen(50, 60, "YOU MUST MOVE FROM THE LEFT SIDE OF THE COURT TO THE RIGHT");
	PrintStringToScreen(50, 50, "USE THE ARROW KEYS TO DODGE BALLS BEING THROWN AT YOU");
	PrintStringToScreen(50, 40, "IF YOU ARE HIT BY 3 BALLS, YOU'RE OUT!");
	PrintStringToScreen(50, 20, "PRESS RETURN TO CONTINUE");
}