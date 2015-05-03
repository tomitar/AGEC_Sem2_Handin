#pragma once
#include "GameObject.h"
class Powerup :	public GameObject
{
public:
	Powerup();
	~Powerup();
	void Render();
	void Update(float deltaTime, SDL_Event e);

	
};