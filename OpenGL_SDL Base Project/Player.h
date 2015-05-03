#pragma once
#include "GameObject.h"
#include "SDL_mixer.h"
#include "Powerup.h"

class Player : public GameObject
{
public:
	Player(MOVEMENT_TYPE moveType);
	~Player();
	void Update(float deltaTime, SDL_Event e);
	void Render();
	void Move(float deltaTime);
	Sphere* GetBoundingSphere();
	void TakeDamage(int damage);
	void SetLives(int value)				{ lives = value; }
	int GetLives()							{ return lives; }
	void SetMoveType(MOVEMENT_TYPE value)	{ moveType = value; }
	MOVEMENT_TYPE GetMoveType()				{ return moveType; }
	void HandleMouseMove(int mouseX, int mouseY);
	PowerupType GetMyPowerup()					{ return myPowerup; }
	void SetMyPowerup(PowerupType value)		{ myPowerup = value; }

	Vector3D GetPlayerPosition()		{ return Vector3D( GameObject::GetPosition().x, GameObject::GetPosition().y, GameObject::GetPosition().z); }

private:
	bool holdingLeft;
	bool holdingRight;
	bool holdingUp;
	bool holdingDown;

	int mMoveX;
	int mMoveY;
	bool mouseMoved;

	int windowMidX;
	int windowMidY;

	int lives;
	PowerupType myPowerup;

	Mix_Chunk *denzilScream;
	MOVEMENT_TYPE moveType;
};