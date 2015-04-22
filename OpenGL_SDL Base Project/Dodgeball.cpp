#include "Dodgeball.h"
#include "Commons.h"
#include <iostream>

Dodgeball::Dodgeball() : GameObject(0,false,COLLISION_SPHERE)
{
	SetHasPhysics(true);
	SetSpeed(Vector3D(	RandomFloat(-7.0f,7.0f),
									0.0f,
							RandomFloat(-7.0f,7.0f)));

	SetPosition(Vector3D(	RandomFloat(-28.0f, 28.0f),
							30.0f,
							RandomFloat(-40.0f, 33.0f)));

	SetModel(position, "Tree.3ds", true, "notext");
}

Dodgeball::~Dodgeball()
{
}

void Dodgeball::Update(float deltaTime, SDL_Event e)
{
	//bounce inelastic
	if (GetPosition().y <= 0.0f)
	{
		SetSpeed(Vector3D(GetSpeed().x, GetSpeed().y*-1.0f, (GetSpeed().z)));
	}

	GameObject::Update(deltaTime,e);
}

void Dodgeball::Render()
{
	GameObject::Render();
	glPushMatrix();
	glTranslatef(GetPosition().x, GetPosition().y, GetPosition().z);
	glColor3f(0.9, 0.1, 0.1);
	glutSolidSphere(1, 10, 10);
	glPopMatrix();
}

float Dodgeball::RandomFloat(float a, float b)
{
	float random = ((float)rand() / (float)RAND_MAX);
	float diff = b - a;
	float r = random*diff;
	return a + r;
}