#pragma once
#include "Commons.h"
#include <string>
#include <SDL.h>
#include "../gl/glut.h"

using std::string;

class ObjectOBJ
{
public:
	ObjectOBJ(Vector3D	startPosition, string	modelFileName, bool visibility);
	~ObjectOBJ(){}
	void update(float deltaTime, SDL_Event e);
	void render(GLenum renderingMode);

	void loadModel();

	void loadTexture();
private:
	Vector3D	mPosition;
	char fileName[20];
	char textureName[20];
	obj_type_2	object;

	material oMaterial;
	material lMaterial;

	bool movementBool;
	bool isVisible;
};