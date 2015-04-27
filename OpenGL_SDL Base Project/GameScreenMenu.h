#pragma once
#include "GameScreen.h"

class GameScreenMenu : GameScreen
{

public:
	GameScreenMenu();
	~GameScreenMenu();

	void Render();
	void Update(float deltaTime, SDL_Event e);
};
