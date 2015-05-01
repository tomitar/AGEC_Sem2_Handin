#pragma once
#include "GameObject.h"
class Target : public GameObject
{
public:
	Target();
	~Target();
	void Update(float deltaTime, SDL_Event e);
	void Render();
};
