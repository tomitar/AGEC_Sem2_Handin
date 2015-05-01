#include "Terrain.h"
#include <cstdio>
#include "Commons.h"

//-----------------------------------------------------------------------------------------------

Terrain::Terrain()
{
	tMaterial = {
		{ 0.0f, 0.0f, 0.0f },
		{ 0.1f, 0.8f, 0.1f },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		100.0f
	};

	wMaterial = {
		{ 0.1f, 0.1f, 0.8f },
		{ 0.1f, 0.1f, 0.8f },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		100.0f
	};
}

//-----------------------------------------------------------------------------------------------

Terrain::~Terrain()
{
}

//-----------------------------------------------------------------------------------------------

bool Terrain::Initialise()
{
	const char heightmapFilename[] = "heightmap.raw";
	FILE *pFile;
	fopen_s(&pFile, heightmapFilename, "rb");
	if (!pFile)
		return false;

	fread(&heightmap, TERRAIN_SIZE * TERRAIN_SIZE, 1, pFile);
	fclose(pFile);

	waterHeight = 2.0f;
	isRising = true;
	maxHeight = getMaxHeight();

	GenerateNormals();

	return true;
}

//-----------------------------------------------------------------------------------------------

unsigned char Terrain::h(int x, int y)
{
	return heightmap[y*TERRAIN_SIZE + x];
}

//-----------------------------------------------------------------------------------------------

float Terrain::getMaxHeight()
{
	float topHeight = 0.0f;
	for (int z = 0; z < TERRAIN_SIZE - 1; ++z)
	{
		for (int x = 0; x < TERRAIN_SIZE; ++x)
		{
			float oneHeight = heightmap[z * TERRAIN_SIZE + x];
			float twoHeight = heightmap[(z + 1)* TERRAIN_SIZE + x];
			if (oneHeight >= twoHeight && oneHeight > maxHeight)
			{
				topHeight = oneHeight;
			}
			else if (twoHeight > maxHeight)
			{
				topHeight = twoHeight;
			}
		}
	}
	return topHeight;
}

//-----------------------------------------------------------------------------------------------

void Terrain::GenerateNormals()
{
	for (unsigned int y = 0; y<TERRAIN_SIZE-1; ++y)
	{
		for (unsigned int x = 0; x<TERRAIN_SIZE; ++x)
		{
			// The ? : and ifs are necessary for the border cases.

			float sx = h(x<TERRAIN_SIZE - 1 ? x + 1 : x, y) - h(x ? x - 1 : x, y);
			if (x == 0 || x == TERRAIN_SIZE - 1)
				sx *= 2;

			float sy = h(x, y<TERRAIN_SIZE - 1 ? y + 1 : y) - h(x, y ? y - 1 : y);
			if (y == 0 || y == TERRAIN_SIZE - 1)
				sy *= 2;

			normals[y*TERRAIN_SIZE + x] = { -sx*SCALE_FACTOR, 2 * SCALE_FACTOR, sy*SCALE_FACTOR };
			double vectorMagnitude = ((normals[y*TERRAIN_SIZE + x].x*normals[y*TERRAIN_SIZE + x].x) + (normals[y*TERRAIN_SIZE + x].y*normals[y*TERRAIN_SIZE + x].y) + (normals[y*TERRAIN_SIZE + x].z*normals[y*TERRAIN_SIZE + x].z));
			if (vectorMagnitude != 0)
			{
				normals[y*TERRAIN_SIZE + x].x /= vectorMagnitude;
				normals[y*TERRAIN_SIZE + x].y /= vectorMagnitude;
				normals[y*TERRAIN_SIZE + x].z /= vectorMagnitude;
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------

void Terrain::Render()
{
	glPushMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GLUT_NORMAL);

	//Draw the terrain
	//Load Terrain Material
	glMaterialfv(GL_FRONT, GL_AMBIENT, tMaterial.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, tMaterial.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, tMaterial.specular);
	glMaterialf(GL_FRONT, GL_SHININESS, tMaterial.shininess);

	for (int z = 0; z < TERRAIN_SIZE - 1; ++z)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (int x = 0; x < TERRAIN_SIZE; ++x)
		{
			//Render two vertices of the strip at once
			float scaledHeight = heightmap[z * TERRAIN_SIZE + x] / SCALE_FACTOR;
			float nextScaledHeight = heightmap[(z + 1)* TERRAIN_SIZE + x] / SCALE_FACTOR;

			//Set the material diffuse based on the height of the vertex.
			if ((((heightmap[z * TERRAIN_SIZE + x]) / maxHeight) / SCALE_FACTOR) > 1.0f)
			{
				tMaterial = { { 0.2f, 0.2f, 0.2f },
				{ 1.0f,
				1.0f,
				1.0f },
				{ 1.0f, 1.0f, 1.0f, 1.0f },
				100.0f };
			}
			else
			{
				tMaterial = { { 0.2f, 0.2f, 0.2f },
				{ (((heightmap[z * TERRAIN_SIZE + x]) / maxHeight) / SCALE_FACTOR),
				(((heightmap[z * TERRAIN_SIZE + x]) / maxHeight) / SCALE_FACTOR),
				1.0f },
				{ 1.0f, 1.0f, 1.0f, 1.0f },
				100.0f };
			}
			glMaterialfv(GL_FRONT, GL_DIFFUSE, tMaterial.diffuse);

			//glTexCoord2f((GLfloat)x/TERRAIN_SIZE*8, (GLfloat)z/TERRAIN_SIZE*8);
			//glNormal3f(normals[z*TERRAIN_SIZE + x].x, normals[z*TERRAIN_SIZE + x].y, normals[z*TERRAIN_SIZE + x].z);
			glVertex3f(static_cast<GLfloat>(x - TERRAIN_SIZE/2), scaledHeight, static_cast<GLfloat>(z - TERRAIN_SIZE/2));

			if ((((heightmap[(z+1) * TERRAIN_SIZE + x]) / maxHeight) / SCALE_FACTOR) > 1.0f)
			{
				tMaterial = { { 0.2f, 0.2f, 0.2f },
				{ 1.0f,
				1.0f,
				1.0f },
				{ 1.0f, 1.0f, 1.0f, 1.0f },
				100.0f };
			}
			else
			{
				tMaterial = { { 0.2f, 0.2f, 0.2f },
				{ (((heightmap[(z + 1) * TERRAIN_SIZE + x]) / maxHeight) / SCALE_FACTOR),
				(((heightmap[(z + 1) * TERRAIN_SIZE + x]) / maxHeight) / SCALE_FACTOR),
				1.0f },
				{ 1.0f, 1.0f, 1.0f, 1.0f },
				100.0f };
			}
			
			glMaterialfv(GL_FRONT, GL_DIFFUSE, tMaterial.diffuse);

			//glTexCoord2f((GLfloat)x/TERRAIN_SIZE*8, (GLfloat)(z+1)/TERRAIN_SIZE*8);
			//glNormal3f(normals[(z+1)*TERRAIN_SIZE + x].x, normals[(z+1)*TERRAIN_SIZE + x].y, normals[(z+1)*TERRAIN_SIZE + x].z);
			glVertex3f(static_cast<GLfloat>(x - TERRAIN_SIZE/2), nextScaledHeight, static_cast<GLfloat>(z + 1 - TERRAIN_SIZE/2));
		}
		glEnd();
	}

	//draw the water
	//Load water material
	/*glMaterialfv(GL_FRONT, GL_AMBIENT, wMaterial.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, wMaterial.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, wMaterial.specular);
	glMaterialf(GL_FRONT, GL_SHININESS, wMaterial.shininess);

	glPolygonMode(GL_FRONT, GL_FILL);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-TERRAIN_SIZE/2.1f, waterHeight, TERRAIN_SIZE/2.1f);

		glTexCoord2f(TERRAIN_SIZE/4.0f, 0.0);
		glVertex3f(TERRAIN_SIZE/2.1f, waterHeight, TERRAIN_SIZE/2.1f);

		glTexCoord2f(TERRAIN_SIZE/4.0f, TERRAIN_SIZE/4.0f);
		glVertex3f(TERRAIN_SIZE/2.1f, waterHeight, -TERRAIN_SIZE/2.1f);

		glTexCoord2f(0.0, TERRAIN_SIZE/4.0f);
		glVertex3f(-TERRAIN_SIZE/2.1f, waterHeight, -TERRAIN_SIZE/2.1f);
	glEnd();

	glPopMatrix();*/
}

//-----------------------------------------------------------------------------------------------

void Terrain::Update(float deltaTime)
{
	switch (isRising)
	{
	case true:
		waterHeight = waterHeight + 0.01f;
		break;
	case false:
		waterHeight = waterHeight - 0.01f;
		break;
	}

	if (waterHeight > 7.0f)
	{
		isRising = false;
	}
	else if (waterHeight < 4.0f)
	{
		isRising = true;
	}
}

//-----------------------------------------------------------------------------------------------

float Terrain::GetHeight(int x, int z)
{
	//heightmap[z * TERRAIN_SIZE + x] / SCALE_FACTOR;
	return heightmap[((z + TERRAIN_SIZE / 2)*TERRAIN_SIZE+(x + TERRAIN_SIZE / 2))]/SCALE_FACTOR;
}