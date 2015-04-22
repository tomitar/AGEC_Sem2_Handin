#pragma once
#include "GameObject.h"
class Dodgeball : GameObject
{
public:
	Dodgeball();
	~Dodgeball();
	void Update(float deltaTime, SDL_Event e);
	void Render();

	float RandomFloat(float a, float b);
};