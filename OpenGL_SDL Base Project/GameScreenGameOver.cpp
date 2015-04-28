#include "GameScreenGameOver.h"


GameScreenGameOver::GameScreenGameOver()
{
}


GameScreenGameOver::~GameScreenGameOver()
{
}


void GameScreenGameOver::Render()
{
	GameScreen::Render();
	PrintStringToScreen(50, 60, "GAME OVER");
}

void GameScreenGameOver::Update(float deltaTime, SDL_Event e)
{
	GameScreen::Update(deltaTime,e);
}