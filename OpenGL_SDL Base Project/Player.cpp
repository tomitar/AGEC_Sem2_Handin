#include "Player.h"
#include "Constants.h"
#include <iostream>
#include <string>


using namespace::std;

Player::Player() : GameObject(100.0f, true, COLLISION_SPHERE)
{
	Player::SetModel(Vector3D(0.0f, 0.0f, 0.0f), "Tree_1.3ds", true, "notexture.tga");
	Player::SetMovementSpeed(15);
	holdingDown = false;
	holdingLeft = false;
	holdingRight = false;
	holdingUp = false;
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

	//double sinXRot = sin(rotation.x * DEG2RAD);
	//double cosXRot = cos(rotation.x * DEG2RAD);

	//double sinYRot = sin(rotation.y * DEG2RAD);
	//double cosYRot = cos(rotation.y * DEG2RAD);

	//double pitchLimitFactor = cosXRot; // This cancels out moving on the Z axis when we're looking up or down

	//if (holdingUp)
	//{
	//	movement.x = (movement.x + (sinYRot * pitchLimitFactor));
	//	movement.y = (movement.y - sinXRot);
	//	movement.z = (movement.z - (cosYRot * pitchLimitFactor));
	//}

	//if (holdingDown)
	//{
	//	movement.x = (movement.x - (sinYRot * pitchLimitFactor));
	//	movement.y = (movement.y + sinXRot);
	//	movement.z = (movement.z + (cosYRot * pitchLimitFactor));
	//}

	//if (holdingLeft)
	//{
	//	movement.x = movement.x - cosYRot;
	//	movement.z = movement.z - sinYRot;
	//}

	//if (holdingRight)
	//{
	//	movement.x = movement.x + cosYRot;
	//	movement.z = movement.z + sinYRot;
	//}

	//// Normalise our movement vector
	//double vectorMagnitude = sqrt((movement.x*movement.x) + (movement.y*movement.y) + (movement.z*movement.z));
	//if (vectorMagnitude != 0)
	//{
	//	movement.x /= vectorMagnitude;
	//	movement.y /= vectorMagnitude;
	//	movement.z /= vectorMagnitude;
	//}

	//// Calculate our value to keep the movement the same speed regardless of the framerate
	//double framerateIndependentFactor = movementSpeed * deltaTime;

	//// apply it to our movement vector.
	//movement.x *= framerateIndependentFactor;
	//movement.y *= framerateIndependentFactor;
	//movement.z *= framerateIndependentFactor;

	//debug
	//cout << "Player Pos" << position.x << " " << position.y << " " << position.z << endl;

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
	//28
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

	//debug
	//cout << "player position: " << position.x << " " << position.y << " " << position.z << endl;
}