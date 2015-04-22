#pragma once
#include "GameObject.h"
class Player : GameObject
{
public:
	Player();
	~Player();
	void Update(float deltaTime, SDL_Event e);
	void Render();
	void Move(float deltaTime);
	Sphere* GetBoundingSphere();
	void TakeDamage(int damage);
	void SetLives(int value)	{ lives = value; }
	int GetLives()				{ return lives; }

private:
	bool holdingLeft;
	bool holdingRight;
	bool holdingUp;
	bool holdingDown;

	int lives;
};