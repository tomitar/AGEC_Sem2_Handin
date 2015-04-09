#include "object3DS.h"
#include "../gl/glut.h"
#include "ModelLoader.h"
#include <SDL.h>
#include "Texture.h"

Object3DS::Object3DS(Vector3D	startPosition, string	modelFileName, bool visibility, string modelTextureName)
{
	//start	position.
	mPosition = startPosition;
	//3ds	file	to	load.
	std::strcpy(fileName, modelFileName.c_str());
	std::strcpy(textureName, modelTextureName.c_str());
	loadModel();

	oMaterial = {
		{ 0.5f, 0.025f, 0.025f },
		{ 0.5f, 0.025f, 0.025f },
		{ 0.5f, 0.025f, 0.025, 1.0f },
		20.0f
	};

	lMaterial = {
		{ 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0, 1.0f },
		100.0f
	};

	movementBool = true;
	isVisible = visibility;
	bounceHeight = 0.0f;

	loadTexture();
}

int Object3DS::loadModel()
{
	if (fileName[0] != '-')
	{
		Load3DS(&object, fileName);
	}
	return 0;
}

void Object3DS::loadTexture()
{
	glEnable(GL_TEXTURE_2D);

	Texture* texture = new Texture();
	if (texture->Load(textureName, 512, 512))
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		object.id_texture = texture->GetID();
	}
	else
	{
		object.id_texture = NULL;
	}
	glDisable(GL_TEXTURE_2D);
}

void Object3DS::update(float deltaTime, SDL_Event e, ANIMMODE animMode)
{
	double framerateIndependentFactor = movementSpeed * deltaTime;

	//Handling constant movement

	switch (animMode){

		case ANIM_STRAFE:

			if (mPosition.x > 50)
			{
				movementBool = false;
			}
			else if (mPosition.x < -50)
			{
				movementBool = true;
			}

			switch (movementBool)
			{
			case true:
				mPosition.x = (mPosition.x + framerateIndependentFactor);
				break;

			case false:
				mPosition.x = (mPosition.x - framerateIndependentFactor);
				break;
			}

		break;

		case ANIM_SPIN:

			if (mRotation.z == 359)
			{
				mRotation.z = 0;
			}
			else
			{
				mRotation.z = (mRotation.z + framerateIndependentFactor);
			}

		break;

		case ANIM_BOUNCE:

			if (bounceHeight >= 1.0f)
			{
				movementBool = false;
			}
			else if (bounceHeight < 0.0f)
			{
				movementBool = true;
			}

			switch (movementBool)
			{
			case true:
				mPosition.y = (mPosition.y + framerateIndependentFactor);
				bounceHeight = (bounceHeight + framerateIndependentFactor);
			break;

			case false:
				mPosition.y = (mPosition.y - framerateIndependentFactor);
				bounceHeight = (bounceHeight - framerateIndependentFactor);
			break;
			}

		/*case ANIM_CUSTOM:

			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_RIGHT:
					mPosition.z = (mPosition.z + framerateIndependentFactor);
				break;

				case SDLK_LEFT:
					mPosition.z = (mPosition.z - framerateIndependentFactor);
				break;

				case SDLK_UP:
					mPosition.x = (mPosition.x + framerateIndependentFactor);
				break;

				case SDLK_DOWN:
					mPosition.x = (mPosition.x - framerateIndependentFactor);
				break;
				}
			}*/
	}
	
	//Manage input

	/*if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_o:
				isVisible = !isVisible;
			break;
		}
	}*/
}

void Object3DS::render(GLenum renderingMode)
{
	if (isVisible)
	{
		glPushMatrix();
		glTranslatef(mPosition.x, mPosition.y, mPosition.z);
		glRotatef(270, 1.0f, 0.0f, 0.0f);
		glRotatef(mRotation.z, 0.0f, 0.0f, 1.0f);
		glScalef(0.05f, 0.05f, 0.05f);
		glPolygonMode(GL_FRONT, renderingMode);

		if (renderingMode == GL_LINE)
		{
			glEnable(GL_COLOR_MATERIAL);
			glMaterialfv(GL_FRONT, GL_AMBIENT, lMaterial.ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, lMaterial.diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, lMaterial.specular);
			glMaterialf(GL_FRONT, GL_SHININESS, lMaterial.shininess);
			glBegin(GL_TRIANGLES);	//	glBegin	and	glEnd	delimit	the	vertices	that	define	a	primitive	(in	our	case	triangles)
			for (int l_index = 0; l_index < object.polygons_qty; l_index++)
			{
				//----------------- FIRST	VERTEX	----------------//
				//	Coordinates	of	the	first	vertex
				glVertex3f(object.vertex[object.polygon[l_index].a].x,
					object.vertex[object.polygon[l_index].a].y,
					object.vertex[object.polygon[l_index].a].z);	
				//----------------- SECOND	VERTEX	-----------------
				//	Coordinates	of	the	second	vertex
				glVertex3f(object.vertex[object.polygon[l_index].b].x,
					object.vertex[object.polygon[l_index].b].y,
					object.vertex[object.polygon[l_index].b].z);

				//----------------- THIRD	VERTEX	-----------------
				//	Coordinates	of	the	Third	vertex
				glVertex3f(object.vertex[object.polygon[l_index].c].x,
					object.vertex[object.polygon[l_index].c].y,
					object.vertex[object.polygon[l_index].c].z);
			}
			glEnd();
			glDisable(GL_COLOR_MATERIAL);
		}
		else if (object.id_texture == NULL)
		{
			glEnable(GL_COLOR_MATERIAL);
			glMaterialfv(GL_FRONT, GL_AMBIENT, oMaterial.ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, oMaterial.diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, oMaterial.specular);
			glMaterialf(GL_FRONT, GL_SHININESS, oMaterial.shininess);
			glBegin(GL_TRIANGLES);	//	glBegin	and	glEnd	delimit	the	vertices	that	define	a	primitive	(in	our	case	triangles)
			for (int l_index = 0; l_index < object.polygons_qty; l_index++)
			{
				//----------------- FIRST	VERTEX	----------------//
				//	Coordinates	of	the	first	vertex
				glVertex3f(object.vertex[object.polygon[l_index].a].x,
					object.vertex[object.polygon[l_index].a].y,
					object.vertex[object.polygon[l_index].a].z);	
				//----------------- SECOND	VERTEX	-----------------
				//	Coordinates	of	the	second	vertex
				glVertex3f(object.vertex[object.polygon[l_index].b].x,
					object.vertex[object.polygon[l_index].b].y,
					object.vertex[object.polygon[l_index].b].z);

				//----------------- THIRD	VERTEX	-----------------
				//	Coordinates	of	the	Third	vertex
				glVertex3f(object.vertex[object.polygon[l_index].c].x,
					object.vertex[object.polygon[l_index].c].y,
					object.vertex[object.polygon[l_index].c].z);
			}
			glEnd();
			glDisable(GL_COLOR_MATERIAL);
		}
		else
		{
			glEnable(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, object.id_texture);	//	We	set	the	active	texture	
			glBegin(GL_TRIANGLES);	//	glBegin	and	glEnd	delimit	the	vertices	that	define	a	primitive	(in	our	case	triangles)
			for (int l_index = 0; l_index < object.polygons_qty; l_index++)
			{
				//----------------- FIRST	VERTEX	----------------//
				//	Texture	coordinates	of	the	first	vertex
				glTexCoord2f(object.mapcoord[object.polygon[l_index].a].u,
					object.mapcoord[object.polygon[l_index].a].v);
				//	Coordinates	of	the	first	vertex
				glVertex3f(object.vertex[object.polygon[l_index].a].x,
					object.vertex[object.polygon[l_index].a].y,
					object.vertex[object.polygon[l_index].a].z);	//Vertex	definition
				//----------------- SECOND	VERTEX	-----------------
				//	Texture	coordinates	of	the	second	vertex
				glTexCoord2f(object.mapcoord[object.polygon[l_index].b].u,
					object.mapcoord[object.polygon[l_index].b].v);
				//	Coordinates	of	the	second	vertex
				glVertex3f(object.vertex[object.polygon[l_index].b].x,
					object.vertex[object.polygon[l_index].b].y,
					object.vertex[object.polygon[l_index].b].z);

				//----------------- THIRD	VERTEX	-----------------
				//	Texture	coordinates	of	the	third	vertex
				glTexCoord2f(object.mapcoord[object.polygon[l_index].c].u,
					object.mapcoord[object.polygon[l_index].c].v);
				//	Coordinates	of	the	Third	vertex
				glVertex3f(object.vertex[object.polygon[l_index].c].x,
					object.vertex[object.polygon[l_index].c].y,
					object.vertex[object.polygon[l_index].c].z);
			}
			glEnd();

			glDisable(GL_TEXTURE_2D);
		}
		
		glPopMatrix();
	}
}
