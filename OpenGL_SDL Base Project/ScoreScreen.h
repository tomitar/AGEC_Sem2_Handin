#pragma once
#include "GameScreen.h"
#include "SDL_mixer.h"

class ScoreScreen :	public GameScreen
{
public:
	ScoreScreen();
	~ScoreScreen();
	
	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	Mix_Chunk *WinSFX;
};

