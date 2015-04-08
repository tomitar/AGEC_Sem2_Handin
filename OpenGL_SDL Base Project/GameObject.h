#pragma once
#include "SDL.h"
#include "Object3DS.h"

class GameObject
{
public:
	GameObject();
	~GameObject();
	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	Object3DS* objectModel;
};

