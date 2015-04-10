#include "Player.h"
#include "Constants.h"
#include <iostream>
#include <string>


using namespace::std;

Player::Player() : GameObject(100.0f, true)
{
	Player::SetModel(Vector3D(0.0f, 0.0f, 0.0f), "Tree_1.3ds", true, "notexture.tga");
	cout << "Player Constructor" << endl;
}


Player::~Player()
{
}

void Player::Render()
{
	cout << "Player Render" << endl;
	GameObject::Render();
}

void Player::Update(float deltaTime, SDL_Event e)
{
	cout << "Player Update" << endl;
	GameObject::Update(deltaTime, e);
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
}

void Player::Move(float deltaTime)
{
	Vector3D movement;

	double sinXRot = sin(rotation.x * DEG2RAD);
	double cosXRot = cos(rotation.x * DEG2RAD);

	double sinYRot = sin(rotation.y * DEG2RAD);
	double cosYRot = cos(rotation.y * DEG2RAD);

	double pitchLimitFactor = cosXRot; // This cancels out moving on the Z axis when we're looking up or down

	if (holdingUp)
	{
		movement.x = (movement.x + (sinYRot * pitchLimitFactor));
		movement.y = (movement.y - sinXRot);
		movement.z = (movement.z - (cosYRot * pitchLimitFactor));
	}

	if (holdingDown)
	{
		movement.x = (movement.x - (sinYRot * pitchLimitFactor));
		movement.y = (movement.y + sinXRot);
		movement.z = (movement.z + (cosYRot * pitchLimitFactor));
	}

	if (holdingLeft)
	{
		movement.x = movement.x - cosYRot;
		movement.z = movement.z - sinYRot;
	}

	if (holdingRight)
	{
		movement.x = movement.x + cosYRot;
		movement.z = movement.z + sinYRot;
	}

	// Normalise our movement vector
	double vectorMagnitude = sqrt((movement.x*movement.x) + (movement.y*movement.y) + (movement.z*movement.z));
	if (vectorMagnitude != 0)
	{
		movement.x /= vectorMagnitude;
		movement.y /= vectorMagnitude;
		movement.z /= vectorMagnitude;
	}

	// Calculate our value to keep the movement the same speed regardless of the framerate
	double framerateIndependentFactor = movementSpeed * deltaTime;

	// apply it to our movement vector.
	movement.x *= framerateIndependentFactor;
	movement.y *= framerateIndependentFactor;
	movement.z *= framerateIndependentFactor;

	// apply the movement to our position
	position.x += movement.x;
	position.y += movement.y;
	position.z += movement.z;

	cout << "player position: " << position.x << " " << position.y << " " << position.z << endl;
}