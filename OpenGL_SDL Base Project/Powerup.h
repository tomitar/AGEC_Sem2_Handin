#pragma once
#include "GameObject.h"
#include "Commons.h"

class Powerup :	public GameObject
{
public:
	Powerup();
	~Powerup();
	void Render();
	void Update(float deltaTime, SDL_Event e);

	PowerupType		GetPType()						{ return myPType; }
	void			SetPType(PowerupType value)		{ myPType = value; }

	bool			GetHasActive()					{ return hasActivated; }
	void			SetHasActive(bool value)		{ hasActivated = value; }

	bool			GetHasFinished();
	
private:
	PowerupType myPType;
	float duration;
	bool hasActivated;
};