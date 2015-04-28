#include "ScoreScreen.h"
#include <sstream>

ScoreScreen::ScoreScreen()
{
}


ScoreScreen::~ScoreScreen()
{
}

void ScoreScreen::Render()
{
	std::stringstream ss;
	ss << GetLevelScore() << std::endl;

	GameScreen::Render();
	PrintStringToScreen(50, 60, "SCORE SCREEN");
	PrintStringToScreen(50, 50, ss.str());
}

void ScoreScreen::Update(float deltaTime, SDL_Event e)
{
	GameScreen::Update(deltaTime, e);
}