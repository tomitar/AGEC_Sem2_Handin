#ifndef _TERRAIN_H
#define _TERRAIN_H

#include "../gl/glut.h"
#include "Constants.h"
#include "Commons.h"

class Terrain
{
//--------------------------------------------------------------------------------------------------
public:
	Terrain();
	~Terrain();

	bool		Initialise();
	void		Render();
	void		Update(float deltaTime);

	float		getMaxHeight();

	void		GenerateNormals();
	unsigned char h(int x, int y);

	material tMaterial;
	material wMaterial;
	Vector3D normals[TERRAIN_SIZE*TERRAIN_SIZE];
	float waterHeight;
	bool isRising;
	float maxHeight;
//--------------------------------------------------------------------------------------------------
private:
	GLubyte heightmap[TERRAIN_SIZE * TERRAIN_SIZE];
};

#endif //_TERRAIN_H