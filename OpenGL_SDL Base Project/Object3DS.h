#pragma once
#include "Commons.h"
#include <string>
#include <SDL.h>
#include "../gl/glut.h"

using std::string;

class Object3DS
{
public:
	Object3DS(Vector3D	startPosition, string	modelFileName, bool visibility, string modelTextureName);
	~Object3DS(){}
	void update(float deltaTime, SDL_Event e, ANIMMODE animMode, Vector3D newPosition);
	void render(GLenum renderingMode);

	int loadModel();

	void loadTexture();

private:
	Vector3D	mPosition;
	Vector3D	mRotation;
	char fileName[20];
	char textureName[20];
	obj_type	object;

	material oMaterial;
	material lMaterial;

	bool movementBool;
	bool isVisible;
	float bounceHeight;
	const float movementSpeed = 10.0f;
};

