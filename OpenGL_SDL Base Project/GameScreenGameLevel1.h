#pragma once
#include "GameScreen.h"
#include "Player.h"
#include "Dodgeball.h"

class GameScreenGameLevel1 : GameScreen
{
public:
	GameScreenGameLevel1();
	~GameScreenGameLevel1();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);

	Player* debugPlayer;
	
	std::vector<Dodgeball*> theDodgeballs;

	float timeSinceStart;
};

