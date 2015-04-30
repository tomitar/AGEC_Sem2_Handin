#pragma once
#include "GameScreen.h"
#include "Player.h"

class GameScreenGameLevel2 : GameScreen
{
public:
	GameScreenGameLevel2();
	~GameScreenGameLevel2();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);

	Player* level2Player;

	//void DrawGround(float groundLevel);
};
