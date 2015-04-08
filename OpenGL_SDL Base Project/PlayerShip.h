#pragma once
#include <iostream>
#include <math.h>
#include <SDL.h>
#include "QuaternionMath.h"
#include "ObjectOBJ.h"

class PlayerShip
{
protected:
	Vector3D position;
	Vector3D rotation;
	Vector3D speed;

	double movementSpeed;
	double pitchSensitivity;
	double yawSensitivity;
	void initShip();
	void getMesh();

public:
	PlayerShip();
	~PlayerShip();

	ObjectOBJ* shipMesh;

	bool holdingForward;
	bool holdingBack;
	bool holdingLeftS;
	bool holdingRightS;

	void move(float deltaTime);
	void Update(float deltaTime, SDL_Event e);
	void Render();

	//Setters
	float getPitchSensitivity()            { return pitchSensitivity; }
	void  setPitchSensitivity(float value) { pitchSensitivity = value; }
	float getYawSensitivity()              { return yawSensitivity; }
	void  setYawSensitivity(float value)   { yawSensitivity = value; }

	//Getters
	Vector3D getPosition() const { return position; }
	double getXPos()           const { return position.x; }
	double getYPos()           const { return position.y; }
	double getZPos()           const { return position.z; }

	Vector3D getRotation() const { return rotation; }
	double getXRot()           const { return rotation.x; }
	double getYRot()           const { return rotation.y; }
	double getZRot()           const { return rotation.z; }
};

