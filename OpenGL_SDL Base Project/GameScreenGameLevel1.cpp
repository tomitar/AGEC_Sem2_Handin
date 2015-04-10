#include "GameScreenGameLevel1.h"
#include "GameObject.h"
#include "Player.h"

#include <iostream>
using namespace::std;

GameScreenGameLevel1::GameScreenGameLevel1()
{
	cout << "GSLV1 constructor" << endl;
	debugPlayer = new Player();
}


GameScreenGameLevel1::~GameScreenGameLevel1()
{
}

void GameScreenGameLevel1::Render()
{
	GameScreen::Render();
	debugPlayer->Render();
}

void GameScreenGameLevel1::Update(float deltaTime, SDL_Event e)
{
	GameScreen::Update(deltaTime, e);
	debugPlayer->Update(deltaTime, e);
}