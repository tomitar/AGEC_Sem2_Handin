#include "Player.h"
#include "Constants.h"
#include <iostream>
#include <string>

using namespace::std;

Player::Player(MOVEMENT_TYPE newMov) : GameObject(100.0f, true, COLLISION_SPHERE,ANIM_CUSTOM)
{
	SetModel(Vector3D(0.0f, 0.0f, 0.0f), "Tree_1.3ds", true, "Ship_1_Texture.raw");
	SetMovementSpeed(15);
	holdingDown = false;
	holdingLeft = false;
	holdingRight = false;
	holdingUp = false;
	SetHasPhysics(false);
	mouseMoved = false;
	SetLifePoints(10);
	SetLives(3);
	denzilScream = NULL;
	denzilScream = Mix_LoadWAV("Scream.wav");
	SetMoveType(newMov);
	windowMidX = SCREEN_WIDTH / 2.0f;
	windowMidY = SCREEN_HEIGHT / 2.0f;

	if (GetMoveType() == MV_FPS)
	{
		SDL_WarpMouseInWindow(NULL, windowMidX, windowMidY);
		yawSensitivity = 0.05f;
		pitchSensitivity = 0.05f;
	}
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
	switch (moveType)
	{
	case MV_TOPDOWN:
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
	break;

	case MV_FPS:
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
			case SDLK_p:
				cout << GetPosition().x << " " << GetPosition().z << endl;
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
		else if (e.type == SDL_MOUSEMOTION)
		{
			mouseMoved = true;
			mMoveX = e.motion.x;
			mMoveY = e.motion.y;
		}
	break;
	}

	Move(deltaTime);

	GameObject::Update(deltaTime, e);
}

void Player::Move(float deltaTime)
{
	Vector3D movement;

	double sinXRot = sin(rotation.x * DEG2RAD);
	double cosXRot = cos(rotation.x * DEG2RAD);

	double sinYRot = sin(rotation.y * DEG2RAD);
	double cosYRot = cos(rotation.y * DEG2RAD);

	double pitchLimitFactor = cosXRot;

	switch (moveType)
	{
	case MV_TOPDOWN:
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
		break;

	case MV_FPS:
		if (holdingUp)
		{
			movement.x = (movement.x + (sinYRot * pitchLimitFactor));
			movement.z = (movement.z - (cosYRot * pitchLimitFactor));
		}
		if (holdingDown)
		{
			movement.x = (movement.x - (sinYRot * pitchLimitFactor));
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
		if (mouseMoved)
		{
			HandleMouseMove(mMoveX, mMoveY);
			mouseMoved = false;
		}

		movement.x *= (movementSpeed*deltaTime);
		movement.y *= (movementSpeed*deltaTime);
		movement.z *= (movementSpeed*deltaTime);

		break;
	}

	// apply the movement to our position

	if (moveType == MV_TOPDOWN)
	{
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

		position.y += movement.y;
	}
	else if (moveType == MV_FPS)
	{
		position.x += movement.x;
		position.y += movement.y;
		position.z += movement.z;
	}

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
	std::cout << GetLives() << std::endl;
	if (lives == -1)
	{
		Mix_PlayChannel(-1, denzilScream, 0);
	}
}

Sphere* Player::GetBoundingSphere()
{
	return GameObject::GetBoundingSphere();
}

void Player::HandleMouseMove(int mouseX, int mouseY)
{
	//Find the distance the mouse has moved since the last frame, and affect
	//the rotation of the camera by that amount. Reset the mouse to the middle
	//of the window.

	double horizMovement = (mouseX - windowMidX + 1)*yawSensitivity;
	double vertMovement = (mouseY - windowMidY)*pitchSensitivity;

	rotation.x = (rotation.x + vertMovement);

	if (rotation.x < -90)
	{
		rotation.x = -90;
	}
	else if (rotation.x > 90)
	{
		rotation.x = 90;
	}

	rotation.y = (rotation.y + horizMovement);

	if (rotation.y < 0)
	{
		rotation.y = (rotation.y + 360);
	}
	else if (rotation.y > 360)
	{
		rotation.y = (rotation.y - 360);
	}

	SDL_WarpMouseInWindow(NULL, windowMidX, windowMidY);
}