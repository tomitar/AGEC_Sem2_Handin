#include "ScoreScreen.h"
#include <sstream>

ScoreScreen::ScoreScreen()
{
	WinSFX = NULL;
	WinSFX = Mix_LoadWAV("applause.wav");
	Mix_PlayChannel(-1, WinSFX, 0);
}


ScoreScreen::~ScoreScreen()
{
	Mix_CloseAudio();
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
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