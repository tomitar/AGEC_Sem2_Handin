#include "Player.h"
#include "Constants.h"
#include <iostream>
#include <string>

using namespace::std;

Player::Player() : GameObject(100.0f, true, COLLISION_SPHERE)
{
	SetModel(Vector3D(0.0f, 0.0f, 0.0f), "Tree_1.3ds", true, "notexture.tga");
	SetMovementSpeed(15);
	holdingDown = false;
	holdingLeft = false;
	holdingRight = false;
	holdingUp = false;
	SetHasPhysics(false);
	SetLifePoints(10);
	SetLives(3);
}


Player::~Player()
{
}

void Player::Render()
{
	GameObject::Render();
}

void Player::Update(float deltaTime, SDL_Event e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			holdingUp = true;
			break;
		case SDLK_s:
			holdingDown = true;
			break;
		case SDLK_a:
			holdingLeft = true;
			break;
		case SDLK_d:
			holdingRight = true;
			break;
		}
	}
	else if (e.type == SDL_KEYUP)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			holdingUp = false;
			break;
		case SDLK_s:
			holdingDown = false;
			break;
		case SDLK_a:
			holdingLeft = false;
			break;
		case SDLK_d:
			holdingRight = false;
			break;
		}
	}
	Move(deltaTime);

	GameObject::Update(deltaTime, e);
}

void Player::Move(float deltaTime)
{
	Vector3D movement;

	if (holdingUp)
	{
		movement.z = (movementSpeed*deltaTime)*(-1);
	}
	if (holdingDown)
	{
		movement.z = movementSpeed*deltaTime;
	}
	if (holdingLeft)
	{
		movement.x = (movementSpeed*deltaTime)*(-1);
	}
	if (holdingRight)
	{
		movement.x = movementSpeed*deltaTime;
	}

	// apply the movement to our position
	//prevent the player from moving off the edge of the screen
	//only applicable to level 1, put walls for more permanent fix
	if (position.z > -40 && position.z < 33)
	{
		position.z += movement.z;
	}		
	else
	{
		if (position.z > -40)
		{
			position.z = position.z - 0.1f;
		}
		else
		{
			position.z = position.z + 0.1f;
		}
	}
	
	if (position.x > -28 && position.x < 28)
	{
		position.x += movement.x;
	}
	else
	{
		if (position.x > -28)
		{
			position.x = position.x - 0.1f;
		}
		else
		{
			position.x = position.x + 0.1f;
		}
	}

//	if ((position.y > -40 || position.y < 33) || (movement.y > 0 && position.y > -40) || (movement.y < 0 && position.y >33))
	position.y += movement.y;
	
	movement.x = 0;
	movement.y = 0;
	movement.z = 0;
}

void Player::TakeDamage(int damage)
{
	SetLifePoints(GetLifePoints() - damage);
	if (GetLifePoints() <= 0)
	{
		SetLives(GetLives() - 1);
		SetLifePoints(10.0f);
	}
}

Sphere* Player::GetBoundingSphere()
{
	return GameObject::GetBoundingSphere();
}