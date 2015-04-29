#pragma once
#include "GameScreen.h"
#include "Player.h"
#include "Dodgeball.h"
#include "Texture.h"
#include <SDL_mixer.h>

class GameScreenGameLevel1 : GameScreen
{
public:
	GameScreenGameLevel1();
	~GameScreenGameLevel1();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);
	void		DrawCourt();

	Player* debugPlayer;
	
	std::vector<Dodgeball*> theDodgeballs;

	float timeSinceStart;

	Texture* courtTexture;

};