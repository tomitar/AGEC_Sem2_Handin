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
	setIsStatic(true);

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

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60, (((SCREEN_WIDTH > SCREEN_HEIGHT) ? float(SCREEN_WIDTH) / float(SCREEN_HEIGHT) : float(SCREEN_HEIGHT) / float(SCREEN_WIDTH)) / 2),
		0.1f, 1000.0f);
}

void Camera::Update(float deltaTime, SDL_Event e)
{
	//if (!getIsStatic())
	//{
	//	//move here
	//}
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
