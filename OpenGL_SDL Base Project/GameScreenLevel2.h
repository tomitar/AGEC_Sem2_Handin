#pragma once
#include <SDL.h>
#include "GameScreen.h"
#include "Commons.h"
#include "Object3DS.h"

class GameScreenLevel2 : GameScreen
{
public:
	GameScreenLevel2();
	~GameScreenLevel2();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	float mCurrentTime;

	Object3DS*	m3DSModel;
	Object3DS* m3DSModel1;

	void DrawGround(float groundLevel);
	void SetLight();

	lighting mLight;
	material gMaterial;
};

