#pragma once
#include "GameObject.h"
class Player : public GameObject
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

	Vector3D GetPlayerPosition()		{ return Vector3D( GameObject::GetPosition().x, GameObject::GetPosition().y, GameObject::GetPosition().z); }

private:
	bool holdingLeft;
	bool holdingRight;
	bool holdingUp;
	bool holdingDown;

	int lives;
};