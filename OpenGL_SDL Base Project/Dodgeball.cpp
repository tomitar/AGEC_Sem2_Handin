#include "Dodgeball.h"
#include "Commons.h"
#include <iostream>

Dodgeball::Dodgeball() : GameObject(0,false,COLLISION_SPHERE)
{
	SetHasPhysics(true);
	SetHasHitPlayer(false);
	SetSpeed(Vector3D(	RandomFloat(-7.0f,7.0f),
									0.0f,
							RandomFloat(-7.0f,7.0f)));

	SetPosition(Vector3D(	RandomFloat(-28.0f, 28.0f),
							30.0f,
							RandomFloat(-40.0f, 33.0f)));

	SetModel(position, "Tree.3ds", true, "notext");

	positionOffset = Vector3D(0.0f, 0.0f, 0.0f);

	bounceWav = NULL;
	bounceWav = Mix_LoadWAV("bounce.wav");
}

Dodgeball::~Dodgeball()
{
}

void Dodgeball::Update(float deltaTime, SDL_Event e)
{
	Vector3D tempPosition;
	if (HasHitPlayer == false)
	{
		//bounce inelastic
		if (GetPosition().y <= 0.0f)
		{
			SetSpeed(Vector3D(GetSpeed().x, GetSpeed().y*-1.0f, (GetSpeed().z)));
			Mix_PlayChannel(-1, bounceWav, 0);
		}
	}
	else
	{
		tempPosition = ParentPlayer->GetPlayerPosition();
		tempPosition.x = tempPosition.x - positionOffset.x;
		tempPosition.y = tempPosition.y - positionOffset.y;
		tempPosition.z = tempPosition.z - positionOffset.z;
		SetPosition(tempPosition);
	}

	GameObject::Update(deltaTime, e);
}

void Dodgeball::Render()
{
	GameObject::Render();
	glPushMatrix();
	glEnable(GL_COLOR);
	glTranslatef(GetPosition().x, GetPosition().y, GetPosition().z);
	glColor3f(0.9, 0.1, 0.1);
	glutSolidSphere(1, 10, 10);
	glDisable(GL_COLOR);
	glPopMatrix();
}

float Dodgeball::RandomFloat(float a, float b)
{
	float random = ((float)rand() / (float)RAND_MAX);
	float diff = b - a;
	float r = random*diff;
	return a + r;
}

bool Dodgeball::PositionCheck()
{
	if (GetHasHitPlayer() == false)
	{
		if (GetPosition().x > 28.0f)
		{
			return false;
		}
		else if (GetPosition().x < -28.0f)
		{
			return false;
		}
		else if (GetPosition().z > 33.0f)
		{
			return false;
		}
		else if (GetPosition().z < -40.0f)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return true;
	}
}

Sphere* Dodgeball::GetBoundingSphere()
{
	return GameObject::GetBoundingSphere();
}

void Dodgeball::SetHasHitPlayer(bool value)		
{ 
	HasHitPlayer = value; 
	if (value == true)
	{
		SetSpeed(Vector3D(0, 0, 0));
		SetHasPhysics(false);
	}
	else
	{
		SetSpeed(Vector3D(	RandomFloat(-7.0f, 7.0f),
							0.0f,
							RandomFloat(-7.0f, 7.0f)));
		SetHasPhysics(true);
	}
}