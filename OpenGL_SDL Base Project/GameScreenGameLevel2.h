#pragma once
#include "GameScreen.h"
#include "Player.h"
#include "Terrain.h"
#include "Target.h"
#include "Powerup.h"

class GameScreenGameLevel2 : GameScreen
{
public:
	GameScreenGameLevel2();
	~GameScreenGameLevel2();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);

	Player* level2Player;
	Terrain* level2Terrain;

	std::vector<Target*>	theTargets;
	std::vector<Powerup*>	thePowerups;
	float targetTime;

	lighting mLight;
	int waveNumber;
	int hitTargets;

	void DrawGround(float groundLevel);
	void TargetWave();
};
