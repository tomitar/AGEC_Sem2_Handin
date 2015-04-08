//This camera class uses components and structure based on the tutorial found here:
//http://r3dux.org/2012/12/a-c-camera-class-for-simple-opengl-fps-controls/

#include "Camera.h"
#include "Constants.h"
#include <SDL.h>
#include "../gl/glut.h"
#include <SDL_image.h>

static Camera* instance = 0;

Camera::Camera()
{
	//Initialise the camera, lock the mouse in place.

	initCamera();

	windowMidX = SCREEN_WIDTH / 2.0f;
	windowMidY = SCREEN_HEIGHT / 2.0f;

	mouseMoved = false;

	SDL_WarpMouseInWindow(NULL, windowMidX, windowMidY);
	instance = this;
}


Camera::~Camera()
{
}

Camera* Camera::GetInstance()
{
	if (instance == 0)
	{
		instance = new Camera();
	}

	return instance;
}

void Camera::initCamera()
{
	//Initialise all our variables

	position.x = 0;
	position.y = 155;
	position.z = 470;

	rotation.x = 0;
	rotation.y = 0;
	rotation.z = 0;

	speed.x = 0;
	speed.y = 0;
	speed.z = 0;

	movementSpeed = 100.0f;

	pitchSensitivity = 0.2;
	yawSensitivity = 0.2;

	holdingForward = false;
	holdingBack = false;
	holdingLeftS = false;
	holdingRightS = false;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60, (((SCREEN_WIDTH > SCREEN_HEIGHT) ? float(SCREEN_WIDTH) / float(SCREEN_HEIGHT) : float(SCREEN_HEIGHT) / float(SCREEN_WIDTH)) / 2),
		0.1f, 1000.0f);
}

void Camera::handleMouseMove(int mouseX, int mouseY)
{
	//Find the distance the mouse has moved since the last frame, and affect
	//the rotation of the camera by that amount. Reset the mouse to the middle
	//of the window.

	double horizMovement = (mouseX - windowMidX + 1)*yawSensitivity;
	double vertMovement = (mouseY - windowMidY)*pitchSensitivity;

	std::cout << "Mid window values: " << windowMidX << "\t" << windowMidY << std::endl;
	std::cout << "Mouse values     : " << mouseX << "\t" << mouseY << std::endl;
	std::cout << horizMovement << "\t" << vertMovement << std::endl << std::endl;

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

void Camera::move(float deltaTime)
{
	Vector3D movement;

	double sinXRot = sin(rotation.x * DEG2RAD);
	double cosXRot = cos(rotation.x * DEG2RAD);

	double sinYRot = sin(rotation.y * DEG2RAD);
	double cosYRot = cos(rotation.y * DEG2RAD);

	double pitchLimitFactor = cosXRot; // This cancels out moving on the Z axis when we're looking up or down

	if (holdingForward)
	{
		movement.x = (movement.x + (sinYRot * pitchLimitFactor));
		movement.y = (movement.y - sinXRot);
		movement.z = (movement.z - (cosYRot * pitchLimitFactor));
	}

	if (holdingBack)
	{
		movement.x = (movement.x - (sinYRot * pitchLimitFactor));
		movement.y = (movement.y + sinXRot);
		movement.z = (movement.z + (cosYRot * pitchLimitFactor));
	}

	if (holdingLeftS)
	{
		movement.x = movement.x - cosYRot;
		movement.z = movement.z - sinYRot;
	}

	if (holdingRightS)
	{
		movement.x = movement.x + cosYRot;
		movement.z = movement.z + sinYRot;
	}

	if (mouseMoved)
	{
		handleMouseMove(mMoveX, mMoveY);
		mouseMoved = false;
	}

	// Normalise our movement vector
	double vectorMagnitude = sqrt((movement.x*movement.x) + (movement.y*movement.y) + (movement.z*movement.z));
	if (vectorMagnitude != 0)
	{
		movement.x /= vectorMagnitude;
		movement.y /= vectorMagnitude;
		movement.z /= vectorMagnitude;
	}

	// Calculate our value to keep the movement the same speed regardless of the framerate...
	double framerateIndependentFactor = movementSpeed * deltaTime;

	// .. and then apply it to our movement vector.
	movement.x *= framerateIndependentFactor;
	movement.y *= framerateIndependentFactor;
	movement.z *= framerateIndependentFactor;

	// Finally, apply the movement to our position
	position.x += movement.x;
	position.y += movement.y;
	position.z += movement.z;

	//Vector3D movement;

	//double sinXRot = sin(rotation.x * DEG2RAD);
	//double cosXRot = cos(rotation.x * DEG2RAD);

	//double sinYRot = sin(rotation.y * DEG2RAD);
	//double cosYRot = cos(rotation.y * DEG2RAD);

	//double pitchLimitFactor = cosXRot; // This cancels out moving on the Z axis when we're looking up or down

	//if (holdingForward)
	//{
	//	movementSpeed = movementSpeed + 1.0f;
	//}

	//if (holdingBack)
	//{
	//	movementSpeed = 0.0f;
	//}

	//if (holdingLeftS)
	//{
	//	movement.x = movement.x - cosYRot;
	//	movement.z = movement.z - sinYRot;
	//}

	//if (holdingRightS)
	//{
	//	movement.x = movement.x + cosYRot;
	//	movement.z = movement.z + sinYRot;
	//}

	//if (mouseMoved)
	//{
	//	handleMouseMove(mMoveX, mMoveY);
	//	mouseMoved = false;
	//}

	////Calc forward movement
	//movement.x = (movement.x + (sinYRot * pitchLimitFactor));
	//movement.y = (movement.y - sinXRot);
	//movement.z = (movement.z - (cosYRot * pitchLimitFactor));

	//// Normalise our movement vector
	//double vectorMagnitude = sqrt((movement.x*movement.x) + (movement.y*movement.y) + (movement.z*movement.z));
	//if (vectorMagnitude != 0)
	//{
	//	movement.x /= vectorMagnitude;
	//	movement.y /= vectorMagnitude;
	//	movement.z /= vectorMagnitude;
	//}

	//// Calculate our value to keep the movement the same speed regardless of the framerate...
	//double framerateIndependentFactor = movementSpeed * deltaTime;

	//// .. and then apply it to our movement vector.
	//movement.x *= framerateIndependentFactor;
	//movement.y *= framerateIndependentFactor;
	//movement.z *= framerateIndependentFactor;

	//// Finally, apply the movement to our position
	//position.x += movement.x;
	//position.y += movement.y;
	//position.z += movement.z;
}

void Camera::Update(float deltaTime, SDL_Event e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{

		case SDLK_a:
			holdingLeftS = true;
			break;

		case SDLK_d:
			holdingRightS = true;
			break;

		case SDLK_w:
			holdingForward = true;
			break;

		case SDLK_s:
			holdingBack = true;
			break;

		}
	}
	else if (e.type == SDL_KEYUP)
	{
		switch (e.key.keysym.sym)
		{

		case SDLK_a:
			holdingLeftS = false;
			break;

		case SDLK_d:
			holdingRightS = false;
			break;

		case SDLK_w:
			holdingForward = false;
			break;

		case SDLK_s:
			holdingBack = false;
			break;

		}
		std::cout << "Pos: " << position.x << ".x " << position.y << ".y " << position.z << ".z" << std::endl;
	}
	else if (e.type == SDL_MOUSEMOTION)
	{
		mouseMoved = true;
		mMoveX = e.motion.x;
		mMoveY = e.motion.y;
	}
	move(deltaTime);
}

void Camera::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset the matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Move the camera to our location in space
	glRotatef(getXRot(), 1.0f, 0.0f, 0.0f); // Rotate our camera on the x-axis (looking up and down)
	glRotatef(getYRot(), 0.0f, 1.0f, 0.0f); // Rotate our camera on the  y-axis (looking left and right)

	// Translate the ModelView matrix to the position of our camera - everything should now be drawn relative
	// to this position!
	glTranslatef(-getXPos(), -getYPos(), -getZPos());
}
