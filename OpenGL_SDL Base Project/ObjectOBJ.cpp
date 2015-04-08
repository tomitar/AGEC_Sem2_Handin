#include "ObjectOBJ.h"
#include "../gl/glut.h"
#include "ModelLoader.h"
#include <SDL.h>

ObjectOBJ::ObjectOBJ(Vector3D	startPosition, string	modelFileName, bool visibility)
{
	//start	position.
	mPosition = startPosition;
	//3ds	file	to	load.
	std::strcpy(fileName, modelFileName.c_str());
	loadModel();

	oMaterial = {
		{ 0.5f, 0.025f, 0.025f },
		{ 0.5f, 0.025f, 0.025f },
		{ 1.0f, 1.0f, 1.0, 1.0f },
		100.0f
	};

	lMaterial = {
		{ 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0, 1.0f },
		100.0f
	};

	movementBool = true;
	isVisible = visibility;
}

void ObjectOBJ::loadModel()
{
	if (fileName[0] != '-')
		LoadOBJ(&object, fileName);
}

void ObjectOBJ::render(GLenum renderingMode)
{
	if (isVisible)
	{
		glPushMatrix();
		glTranslatef(mPosition.x, mPosition.y, mPosition.z);
		glPolygonMode(GL_FRONT, renderingMode);
		if (renderingMode == GL_FILL)
		{
			//Load Material
			glMaterialfv(GL_FRONT, GL_AMBIENT, oMaterial.ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, oMaterial.diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, oMaterial.specular);
			glMaterialf(GL_FRONT, GL_SHININESS, oMaterial.shininess);
		}
		else if (renderingMode == GL_LINE)
		{
			glMaterialfv(GL_FRONT, GL_AMBIENT, lMaterial.ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, lMaterial.diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, lMaterial.specular);
			glMaterialf(GL_FRONT, GL_SHININESS, lMaterial.shininess);
		}

		//glBindTexture(GL_TEXTURE_2D,	object.id_texture);	//	We	set	the	active	texture	
		glBegin(GL_TRIANGLES);	//	glBegin	and	glEnd	delimit	the	vertices	that	define	a	primitive	(in	our	case	triangles)
		for (int l_index = 0; l_index < object.polygons_qty; l_index++)
		{
			//----------------- FIRST	VERTEX	----------------//
			//	Texture	coordinates	of	the	first	vertex
			//glTexCoord2f(	object.mapcoord[	object.polygon[l_index].a	].u,
			// 		object.mapcoord[	object.polygon[l_index].a	].v);
			//	Coordinates	of	the	first	vertex
			glVertex3f(object.vertex[object.polygon[l_index].a].x,
				object.vertex[object.polygon[l_index].a].y,
				object.vertex[object.polygon[l_index].a].z);	//Vertex	definition
			//----------------- SECOND	VERTEX	-----------------
			//	Texture	coordinates	of	the	second	vertex
			//glTexCoord2f(	object.mapcoord[	object.polygon[l_index].b	].u,
			// 		object.mapcoord[	object.polygon[l_index].b	].v);
			//	Coordinates	of	the	second	vertex
			glVertex3f(object.vertex[object.polygon[l_index].b].x,
				object.vertex[object.polygon[l_index].b].y,
				object.vertex[object.polygon[l_index].b].z);

			//----------------- THIRD	VERTEX	-----------------
			//	Texture	coordinates	of	the	third	vertex
			//glTexCoord2f(	object.mapcoord[	object.polygon[l_index].c	].u,
			// 		object.mapcoord[	object.polygon[l_index].c	].v);
			//	Coordinates	of	the	Third	vertex
			glVertex3f(object.vertex[object.polygon[l_index].c].x,
				object.vertex[object.polygon[l_index].c].y,
				object.vertex[object.polygon[l_index].c].z);
		}
		glEnd();
		glPopMatrix();
	}
}

void ObjectOBJ::update(float deltaTime, SDL_Event e)
{

}