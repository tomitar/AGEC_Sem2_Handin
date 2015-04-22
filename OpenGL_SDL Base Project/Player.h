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
	Sphere* GetBoundingSphere()	{ return GetBoundingSphere(); }

private:
	bool holdingLeft;
	bool holdingRight;
	bool holdingUp;
	bool holdingDown;
};