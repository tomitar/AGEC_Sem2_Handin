#pragma once
#include <SDL.h>
#include "GameScreen.h"
#include "Commons.h"
#include "Object3DS.h"

class GameScreenLevel3 : GameScreen
{
public:
	GameScreenLevel3();
	~GameScreenLevel3();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	float mCurrentTime;

	Object3DS*	m3DSModel;

	void SetLight();

	lighting mLight;
};

