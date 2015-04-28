#pragma once
#include "GameScreen.h"
class GameScreenGameOver :	GameScreen
{
public:
	GameScreenGameOver();
	~GameScreenGameOver();

	void Render();
	void Update(float deltaTime, SDL_Event e);
};