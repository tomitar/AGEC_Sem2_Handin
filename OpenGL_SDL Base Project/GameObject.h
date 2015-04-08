#pragma once
#include "SDL.h"
#include "Object3DS.h"

class GameObject
{
public:

	//Engine compulsorys
	GameObject(float startLifePoints, bool startIsDestructable);
	~GameObject();
	void Render();
	void Update(float deltaTime, SDL_Event e);

	//Getters and Setters
	float GetLifePoints();
	bool GetIsDestructable();

	void SetLifePoints(float SetPoints);
	void SetIsDestructable(bool newDestructable);

private:
	Object3DS* objectModel;
	float lifePoints;
	bool isDestructable;
};

