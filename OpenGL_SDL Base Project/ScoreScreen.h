#pragma once
#include "GameScreen.h"
class ScoreScreen :	public GameScreen
{
public:
	ScoreScreen();
	~ScoreScreen();
	
	void Render();
	void Update(float deltaTime, SDL_Event e);
};

